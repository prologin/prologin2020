// This file was generated by stechec2-generator. DO NOT EDIT.

/**
 * Erreurs possibles
 */
enum Erreur {
    /**
     * L'action s'est effectuée avec succès
     */
    OK,
    /**
     * Il est interdit de faire des actions hors de jouer_tour
     */
    HORS_TOUR,
    /**
     * La case désignée n'est pas dans le potager
     */
    HORS_POTAGER,
    /**
     * Il y a déjà une plante sur la case ciblée
     */
    CASE_OCCUPEE,
    /**
     * Il n'y a pas de plante sur la case ciblée
     */
    PAS_DE_PLANTE,
    /**
     * La plante n'appartient pas au bon jardinier
     */
    MAUVAIS_JARDINIER,
    /**
     * La plante est déjà dépotée
     */
    SANS_POT,
    /**
     * La plante a déjà été arrosée
     */
    DEJA_ARROSEE,
    /**
     * La plante a déjà baffé ce tour ci
     */
    DEJA_BAFFEE,
    /**
     * La plante n'a pas encore été arrosée
     */
    PAS_ENCORE_ARROSEE,
    /**
     * La plante ne peut pas encore être arrosée
     */
    PAS_ENCORE_ADULTE,
    /**
     * Les caractéristiques de la plante sont invalides
     */
    PLANTE_INVALIDE,
    /**
     * La plante n'a pas un assez grand rayon de dépotage
     */
    TROP_LOIN,
    /**
     * Valeur de `Caracteristique` inconnue
     */
    CARACTERISTIQUE_INVALIDE,
    /**
     * Valeur de `Chien` inconnue
     */
    CHIEN_INVALIDE,
}

/**
 * Types d'actions
 */
enum ActionType {
    /**
     * Action ``depoter``
     */
    ACTION_DEPOTER,
    /**
     * Action ``baffer``
     */
    ACTION_BAFFER,
    /**
     * Action ``arroser``
     */
    ACTION_ARROSER,
}

/**
 * Caractéristiques améliorables d'une plante
 */
enum Caracteristique {
    /**
     * Force
     */
    CARACTERISTIQUE_FORCE,
    /**
     * Vie
     */
    CARACTERISTIQUE_VIE,
    /**
     * Élégance
     */
    CARACTERISTIQUE_ELEGANCE,
    /**
     * Portée de dépotage
     */
    CARACTERISTIQUE_RAYON_DEPOTAGE,
}

/**
 * Types de chien de débug
 */
enum DebugChien {
    /**
     * Aucun chien, enlève le chien présent
     */
    AUCUN_CHIEN,
    /**
     * Chien bleu
     */
    CHIEN_BLEU,
    /**
     * Chien vert
     */
    CHIEN_VERT,
    /**
     * Chien rouge
     */
    CHIEN_ROUGE,
}

/**
 * Position dans le jardin, donnée par deux coordonnées.
 */
class Position {
    /**
     * Coordonnée : x
     */
    public int x;
    /**
     * Coordonnée : y
     */
    public int y;
}

/**
 * Une plante
 */
class Plante {
    /**
     * Position de la plante
     */
    public Position pos = new Position();
    /**
     * Jardinier ayant planté la plante
     */
    public int jardinier;
    /**
     * La plante est adulte
     */
    public boolean adulte;
    /**
     * La plante a déjà été dépotée
     */
    public boolean enracinee;
    /**
     * Point(s) de vie restant(s) de la plante
     */
    public int vie;
    /**
     * Point(s) de vie maximum de la plante
     */
    public int vie_max;
    /**
     * Force de la baffe de la plante
     */
    public int force;
    /**
     * Élégance de la plante
     */
    public int elegance;
    /**
     * Distance maximale parcourable par la plante en creusant
     */
    public int rayon_deplacement;
    /**
     * Rayon de collecte des ressources pour la plante
     */
    public int rayon_collecte;
    /**
     * Quantité de ressources consommées par la plante
     */
    public int[] consommation;
    /**
     * Âge de la plante
     */
    public int age;
}

/**
 * Représentation d'une action dans l'historique
 */
class ActionHist {
    /**
     * Type de l'action
     */
    public ActionType atype;
    /**
     * Position de la plante baffante (si type d'action ``action_baffer``)
     */
    public Position position_baffante = new Position();
    /**
     * Position de la plante baffée (si type d'action ``action_baffer``)
     */
    public Position position_baffee = new Position();
    /**
     * Position de la plante à déplacer (si type d'action ``action_depoter``)
     */
    public Position position_depart = new Position();
    /**
     * Position où déplacer la plante (si type d'action ``action_depoter``)
     */
    public Position position_arrivee = new Position();
    /**
     * Position de la plante  (si type d'action ``action_arroser``)
     */
    public Position position_plante = new Position();
    /**
     * Caractéristique à améliorer (si type d'action ``action_arroser``)
     */
    public Caracteristique amelioration;
}

public class Api
{
    /**
     * Nombre de jardiniers
     */
    public static final int NB_JARDINIERS = 2;

    /**
     * Largeur et hauteur de la grille
     */
    public static final int TAILLE_GRILLE = 20;

    /**
     * Nombre de tours à jouer avant la fin de la partie
     */
    public static final int NB_TOURS = 100;

    /**
     * Durée de vie maximale d'une plante
     */
    public static final int AGE_MAX = 10;

    /**
     * Âge auquel la plante atteint la maturité et peut donc être arrosée
     */
    public static final int AGE_DE_POUSSE = 3;

    /**
     * Portée maximale d'une baffe
     */
    public static final int PORTEE_BAFFE = 6;

    /**
     * Types de ressources existantes
     */
    public static final int NB_TYPES_RESSOURCES = 3;

    /**
     * Apport pour une caractéristique lors de l'arrosage
     */
    public static final int APPORT_CARACTERISTIQUE = 10;

    /**
     * Nombre de points de caractéristiques nécessaires pour pouvoir dépoter
     * une cases plus loins.
     */
    public static final int COUT_PAR_CASE_COLLECTE = 15;

    /**
     * Nombre de points de caractéristiques nécessaires pour pouvoir dépoter
     * une case plus loin.
     */
    public static final int COUT_PAR_CASE_DEPOTAGE = 15;

    /**
     * La plante creuse vers une destination donnée
     */
    public static native Erreur depoter(Position position_depart, Position position_arrivee);

    /**
     * Arrose une plante
     */
    public static native Erreur arroser(Position position_plante, Caracteristique amelioration);

    /**
     * Une plante en gifle une autre
     */
    public static native Erreur baffer(Position position_baffante, Position position_baffee);

    /**
     * Affiche le chien spécifié sur la case indiquée
     */
    public static native Erreur debug_afficher_chien(Position pos, DebugChien chien);

    /**
     * Renvoie la liste des plantes du jardinier
     */
    public static native Plante[] plantes_jardinier(int jardinier);

    /**
     * Renvoie la plante sur la position donnée, s'il n'y en a pas tous les
     * champs sont initialisés à -1
     */
    public static native Plante plante_sur_case(Position pos);

    /**
     * Renvoie la liste des plantes du jardinier qui peuvent être arrosées
     */
    public static native Plante[] plantes_arrosables(int jardinier);

    /**
     * Renvoie la liste des plantes du jardinier qui sont adultes
     */
    public static native Plante[] plantes_adultes(int jardinier);

    /**
     * Renvoie la liste des plantes du jardinier qui peuvent être dépotées
     */
    public static native Plante[] plantes_depotables(int jardinier);

    /**
     * Renvoie les ressources disponibles sur une case donnée
     */
    public static native int[] ressources_sur_case(Position pos);

    /**
     * Vérifie si une plante à la position donnée aura suffisamment de
     * ressources pour se reproduire. S'il y a déjà une plante à cette
     * position, le calcul suposera qu'elle a été remplacée
     */
    public static native boolean reproduction_possible(Position pos, int rayon_collecte, int[] consommation);

    /**
     * Vérifie si une plante à la position donnée peut se reproduire, retourne
     * faux s'il n'y pas de plante à la position donnée
     */
    public static native boolean plante_reproductible(Position pos);

    /**
     * Caractéristiques d'une plante résultant du croisement de plusieurs
     * parents donnés. Les champs sont initialisés à -1 si aucune plante n'est
     * donnée en paramètre
     */
    public static native Plante croisement(Plante[] parents);

    /**
     * Renvoie la liste des actions effectuées par l’adversaire durant son
     * tour, dans l'ordre chronologique. Les actions de débug n'apparaissent
     * pas dans cette liste.
     */
    public static native ActionHist[] historique();

    /**
     * Renvoie le score du jardinier ``id_jardinier``. Renvoie -1 si le
     * jardinier est invalide.
     */
    public static native int score(int id_jardinier);

    /**
     * Renvoie votre numéro de jardinier.
     */
    public static native int moi();

    /**
     * Renvoie le numéro du jardinier adverse.
     */
    public static native int adversaire();

    /**
     * Annule la dernière action. Renvoie faux quand il n'y a pas d'action à
     * annuler ce tour ci.
     */
    public static native boolean annuler();

    /**
     * Retourne le numéro du tour actuel.
     */
    public static native int tour_actuel();

    /**
     * Affiche le contenu d'une valeur de type erreur
     */
    public static native void afficher_erreur(Erreur v);

    /**
     * Affiche le contenu d'une valeur de type action_type
     */
    public static native void afficher_action_type(ActionType v);

    /**
     * Affiche le contenu d'une valeur de type caracteristique
     */
    public static native void afficher_caracteristique(Caracteristique v);

    /**
     * Affiche le contenu d'une valeur de type debug_chien
     */
    public static native void afficher_debug_chien(DebugChien v);

    /**
     * Affiche le contenu d'une valeur de type position
     */
    public static native void afficher_position(Position v);

    /**
     * Affiche le contenu d'une valeur de type plante
     */
    public static native void afficher_plante(Plante v);

    /**
     * Affiche le contenu d'une valeur de type action_hist
     */
    public static native void afficher_action_hist(ActionHist v);
}
