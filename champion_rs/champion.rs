// Include standard library in documentation: `cargo doc --open`
#[doc(inline)]
pub use std;

pub mod api;
mod ffi;

use std::cmp::Ordering;

use api::*;

macro_rules! print {
    ( $txt:literal $(, $param:expr)* ) => {
        if moi() < adversaire() {
            std::print!($txt $(, $param )*);
        }
    };
}

macro_rules! println {
    ( $txt:literal $(, $param:expr)* ) => {
        if moi() < adversaire() {
            std::println!($txt $(, $param )*);
        }
    }
}

fn display_map() {
    for y in 0..TAILLE_GRILLE {
        for x in 0..TAILLE_GRILLE {
            let c = match plante_sur_case((x, y)).jardinier {
                x if x == moi() => '+',
                x if x == adversaire() => 'o',
                -1 => ' ',
                _ => panic!("unknown jardinier was returned"),
            };

            print!("{}", c);
        }

        println!("");
    }
}

// --- Higher level API wrappers

impl Into<Result<(), Erreur>> for Erreur {
    fn into(self) -> Result<(), Erreur> {
        match self {
            Erreur::Ok => Ok(()),
            err => Err(err),
        }
    }
}

fn arroser(position: (i32, i32), amelioration: Caracteristique) -> Result<(), Erreur> {
    api::arroser(position, amelioration).into()
}

fn baffer(baffante: (i32, i32), baffee: (i32, i32)) -> Result<(), Erreur> {
    api::baffer(baffante, baffee).into()
}

fn depoter(depart: (i32, i32), arrivee: (i32, i32)) -> Result<(), Erreur> {
    api::depoter(depart, arrivee).into()
}

// --- Extra API functions

fn case_pleine(pos: (i32, i32)) -> bool {
    plante_sur_case(pos).vie_max != -1
}

// --- Grid computations

fn full_grid() -> impl Iterator<Item = (i32, i32)> {
    (0..TAILLE_GRILLE)
        .map(|y| (0..TAILLE_GRILLE).map(move |x| (x, y)))
        .flatten()
}

fn circle(center: (i32, i32), radius: i32) -> impl Iterator<Item = (i32, i32)> {
    full_grid().filter(move |&pos| dist(center, pos) <= radius)
}

fn dist(pos1: (i32, i32), pos2: (i32, i32)) -> i32 {
    (pos1.0 - pos2.0).abs() + (pos1.1 - pos2.1).abs()
}

/// Fonction appelée au début de la partie.
pub fn partie_init() {
    println!("=== Start: {} vs. {}", moi(), adversaire());
}

/// Fonction appelée à chaque tour.
pub fn jouer_tour() {
    println!("--- Tour {}", tour_actuel());

    // Arrosage

    for plant in plantes_arrosables(moi()) {
        arroser(plant.pos, Caracteristique::CaracteristiqueElegance).expect("arrosage failed");
    }

    // Depotage

    for plant in plantes_depotables(moi()) {
        let mut candidates: Vec<_> =
            circle(plant.pos, plant.rayon_deplacement / COUT_PAR_CASE_DEPOTAGE)
                .filter(|(x, y)| (x + y) % 2 == 0)
                .filter(|&pos| !case_pleine(pos))
                .collect();

        candidates.sort_by_key(|&pos| {
            plantes_jardinier(moi())
                .into_iter()
                .map(|plant| plant.pos)
                .filter(|&plant_pos| plant_pos != pos)
                .map(|plant_pos| dist(pos, plant_pos))
                .min()
                .unwrap_or(i32::MAX)
        });

        if let Some(&dest) = candidates.first() {
            depoter(plant.pos, dest).expect("depotage failed");
        }
    }

    // Baffes

    for plant in plantes_adultes(moi()) {
        let mut candidates: Vec<_> = plantes_jardinier(adversaire())
            .into_iter()
            .filter(|plant_adv| dist(plant.pos, plant_adv.pos) <= PORTEE_BAFFE)
            .collect();

        candidates.sort_by_key(|plant_adv| plant_adv.vie);

        if let Some(victim) = candidates.first() {
            baffer(plant.pos, victim.pos).expect("baffe failed");
        }
    }

    display_map();
}

/// Fonction appelée à la fin de la partie.
pub fn partie_fin() {
    let ending = match score(moi()).cmp(&score(adversaire())) {
        Ordering::Less => "Defeat",
        Ordering::Equal => "Draw",
        Ordering::Greater => "Victory",
    };

    println!(
        "=== {}: {} to {}",
        ending,
        score(moi()),
        score(adversaire())
    );
}
