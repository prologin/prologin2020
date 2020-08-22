// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (c) 2020 Association Prologin <association@prologin.org>

// This file contains the code to call the API functions from the Python
// language.
// This file was generated by stechec2-generator. DO NOT EDIT.

#include <Python.h>
#include <vector>
#include <string>

static PyObject* py_module;
static PyObject* champ_module;


/// Erreurs possibles
typedef enum erreur
{
    OK, ///< L'action s'est effectuée avec succès
    HORS_TOUR, ///< Il est interdit de faire des actions hors de jouer_tour
    HORS_POTAGER, ///< La case désignée n'est pas dans le potager
    CASE_OCCUPEE, ///< Il y a déjà une plante sur la case ciblée
    PAS_DE_PLANTE, ///< Il n'y a pas de plante sur la case ciblée
    MAUVAIS_JARDINIER, ///< La plante n'appartient pas au bon jardinier
    SANS_POT, ///< La plante est déjà dépotée
    DEJA_ARROSEE, ///< La plante a déjà été arrosée
    DEJA_BAFFEE, ///< La plante a déjà baffé ce tour ci
    PAS_ENCORE_ARROSEE, ///< La plante n'as pas encore été arrosée
    PAS_ENCORE_ADULTE, ///< La plante ne peut pas encore être arrosée
    PLANTE_INVALIDE, ///< Les caractéristiques de la plante sont invalides
    TROP_LOIN, ///< La plante n'a pas un assez grand rayon de dépotage
    CARACTERISTIQUE_INVALIDE, ///< Valeur de `Caracteristique` inconnue
    CHIEN_INVALIDE, ///< Valeur de `Chien` inconnue
} erreur;

/// Types d'actions
typedef enum action_type
{
    ACTION_DEPOTER, ///< Action ``depoter``
    ACTION_BAFFER, ///< Action ``baffer``
    ACTION_ARROSER, ///< Action ``arroser``
} action_type;

/// Caractéristiques améliorables d'une plante
typedef enum caracteristique
{
    CARACTERISTIQUE_FORCE, ///< Force
    CARACTERISTIQUE_VIE, ///< Vie 
    CARACTERISTIQUE_ELEGANCE, ///< Élégance
    CARACTERISTIQUE_RAYON_DEPOTAGE, ///< Portée de dépotage
} caracteristique;

/// Types de chien de débug
typedef enum debug_chien
{
    AUCUN_CHIEN, ///< Aucun chien, enlève le chien présent
    CHIEN_BLEU, ///< Chien bleu
    CHIEN_VERT, ///< Chien vert
    CHIEN_ROUGE, ///< Chien rouge
} debug_chien;

/// Position dans le jardin, donnée par deux coordonnées.
typedef struct position
{
    int x; ///< Coordonnée : x
    int y; ///< Coordonnée : y
} position;

/// Une plante
typedef struct plante
{
    position pos; ///< Position de la plante
    int jardinier; ///< Jardinier ayant planté la plante
    bool adulte; ///< La plante est adulte
    bool enracinee; ///< La plante a déjà déjà été dépotée
    int vie; ///< Point(s) de vie restant(s) de la plante
    int vie_max; ///< Point(s) de vie maximumde la plante
    int force; ///< Force de la baffe de la plante
    int elegance; ///< Élégance de la plante
    int rayon_deplacement; ///< Distance maximale parcourable par la plante en creusant
    int rayon_collecte; ///< Rayon de collecte des ressources pour la plante
    std::vector<int> consommation; ///< Quantité de ressources consommées par la plante
    int age; ///< Âge de la plante
} plante;

/// Représentation d'une action dans l'historique
typedef struct action_hist
{
    action_type atype; ///< Type de l'action
    position position_baffante; ///< Position de la plante baffante (si type d'action ``action_baffer``)
    position position_baffee; ///< Position de la plante baffée (si type d'action ``action_baffer``)
    position position_depart; ///< Position de la plante à déplacer (si type d'action ``action_depoter``)
    position position_arrivee; ///< Position où déplacer la plante (si type d'action ``action_depoter``)
    position position_plante; ///< Position de la plante  (si type d'action ``action_arroser``)
    caracteristique amelioration; ///< Caractéristique à améliorer (si type d'action ``action_arroser``)
} action_hist;

extern "C" {

/// La plante creuse vers une destination donnée
erreur api_depoter(position position_depart, position position_arrivee);

/// Arrose une plante
erreur api_arroser(position position_plante, caracteristique amelioration);

/// Une plante en gifle une autre
erreur api_baffer(position position_baffante, position position_baffee);

/// Affiche le chien spécifié sur la case indiquée
erreur api_debug_afficher_chien(position pos, debug_chien chien);

/// Renvoie la liste des plantes du jardinier
std::vector<plante> api_plantes_jardinier(int jardinier);

/// Renvoie la plante sur la position donnée, s'il n'y en a pas tous les champs
/// sont initialisés à -1
plante api_plante_sur_case(position pos);

/// Renvoie la liste des plantes du jardinier qui peuvent être arrosées
std::vector<plante> api_plantes_arrosables(int jardinier);

/// Renvoie la liste des plantes du jardinier qui sont adultes
std::vector<plante> api_plantes_adultes(int jardinier);

/// Renvoie la liste des plantes du jardinier qui peuvent être dépotées
std::vector<plante> api_plantes_depotables(int jardinier);

/// Renvoie les ressources disponibles sur une case donnée
std::vector<int> api_ressources_sur_case(position pos);

/// Vérifie si une plante à la position donnée aura suffisamment de ressources
/// pour se reproduire. S'il y a déjà une plante à cette position, le calcul
/// suposera qu'elle a été remplacée
bool api_reproduction_possible(position pos, int rayon_collecte, std::vector<int> consommation);

/// Vérifie si une plante à la position donnée peut se reproduire, retourne
/// faux s'il n'y pas de plante à la position donnée
bool api_plante_reproductible(position pos);

/// Caractéristiques d'une plante résultant du croisement de plusieurs parents
/// donnés. Les champs sont initialisés à -1 si aucune plante n'est donnée en
/// paramètre
plante api_croisement(std::vector<plante> parents);

/// Renvoie la liste des actions effectuées par l’adversaire durant son tour,
/// dans l'ordre chronologique. Les actions de débug n'apparaissent pas dans
/// cette liste.
std::vector<action_hist> api_historique();

/// Renvoie le score du jardinier ``id_jardinier``. Renvoie -1 si le jardinier
/// est invalide.
int api_score(int id_jardinier);

/// Renvoie votre numéro de jardinier.
int api_moi();

/// Renvoie le numéro du jardinier adverse.
int api_adversaire();

/// Annule la dernière action. Renvoie faux quand il n'y a pas d'action à
/// annuler ce tour ci.
bool api_annuler();

/// Retourne le numéro du tour actuel.
int api_tour_actuel();

/// Affiche le contenu d'une valeur de type erreur
void api_afficher_erreur(erreur v);

/// Affiche le contenu d'une valeur de type action_type
void api_afficher_action_type(action_type v);

/// Affiche le contenu d'une valeur de type caracteristique
void api_afficher_caracteristique(caracteristique v);

/// Affiche le contenu d'une valeur de type debug_chien
void api_afficher_debug_chien(debug_chien v);

/// Affiche le contenu d'une valeur de type position
void api_afficher_position(position v);

/// Affiche le contenu d'une valeur de type plante
void api_afficher_plante(plante v);

/// Affiche le contenu d'une valeur de type action_hist
void api_afficher_action_hist(action_hist v);
}

template <typename PythonType, typename CxxType>
PythonType cxx_to_python(CxxType in)
{
    return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <>
PyObject* cxx_to_python<PyObject*, int>(int in)
{
    return PyLong_FromLong(in);
}


template <>
PyObject* cxx_to_python<PyObject*, double>(double in)
{
    return PyFloat_FromDouble(in);
}


template <>
PyObject* cxx_to_python<PyObject*, std::string>(std::string in)
{
    return PyUnicode_FromString(in.c_str());
}


template <>
PyObject* cxx_to_python<PyObject*, bool>(bool in)
{
    return PyBool_FromLong(in);
}

template <typename CxxType>
PyObject* cxx_to_python_array(const std::vector<CxxType>& in)
{
    size_t size = in.size();
    PyObject* out = PyList_New(size);

    for (unsigned int i = 0; i < size; ++i)
        PyList_SET_ITEM(out, i, (cxx_to_python<PyObject*, CxxType>(in[i])));

    return out;
}

template <typename PythonType, typename CxxType>
CxxType python_to_cxx(PythonType in)
{
    return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <>
int python_to_cxx<PyObject*, int>(PyObject* in)
{
    long out = PyLong_AsLong(in);
    if (PyErr_Occurred())
        throw 42;
    return out;
}

template <>
double python_to_cxx<PyObject*, double>(PyObject* in)
{
    double out = PyFloat_AsDouble(in);
    if (PyErr_Occurred())
        throw 42;
    return out;
}

template <>
bool python_to_cxx<PyObject*, bool>(PyObject* in)
{
    return static_cast<bool>(python_to_cxx<PyObject*, int>(in));
}

template <>
std::string python_to_cxx<PyObject*, std::string>(PyObject* in)
{
    const char* out = PyUnicode_AsUTF8(in);
    if (PyErr_Occurred())
        throw 42;
    return out;
}

template <typename CxxType>
std::vector<CxxType> python_to_cxx_array(PyObject* in)
{
    if (!PyList_Check(in))
    {
        PyErr_SetString(PyExc_TypeError, "a list is required");
        throw 42;
    }

    std::vector<CxxType> out;
    unsigned int size = PyList_Size(in);
    out.reserve(size);

    for (unsigned int i = 0; i < size; ++i)
        out.push_back(python_to_cxx<PyObject*, CxxType>(PyList_GET_ITEM(in, i)));

    return out;
}

// Erreurs possibles

template<>
PyObject* cxx_to_python<PyObject*, erreur>(erreur in)
{
    PyObject* name = PyUnicode_FromString("erreur");
    PyObject* enm = PyObject_GetAttr(py_module, name);
    Py_DECREF(name);
    if (enm == nullptr)
        throw 42;
    PyObject* arglist = Py_BuildValue("(i)", static_cast<int>(in));
    PyObject* ret = PyObject_CallObject(enm, arglist);
    Py_DECREF(enm);
    Py_DECREF(arglist);
    return ret;
}

template <>
erreur python_to_cxx<PyObject*, erreur>(PyObject* in)
{
    return static_cast<erreur>(python_to_cxx<PyObject*, int>(in));
}

// Types d'actions

template<>
PyObject* cxx_to_python<PyObject*, action_type>(action_type in)
{
    PyObject* name = PyUnicode_FromString("action_type");
    PyObject* enm = PyObject_GetAttr(py_module, name);
    Py_DECREF(name);
    if (enm == nullptr)
        throw 42;
    PyObject* arglist = Py_BuildValue("(i)", static_cast<int>(in));
    PyObject* ret = PyObject_CallObject(enm, arglist);
    Py_DECREF(enm);
    Py_DECREF(arglist);
    return ret;
}

template <>
action_type python_to_cxx<PyObject*, action_type>(PyObject* in)
{
    return static_cast<action_type>(python_to_cxx<PyObject*, int>(in));
}

// Caractéristiques améliorables d'une plante

template<>
PyObject* cxx_to_python<PyObject*, caracteristique>(caracteristique in)
{
    PyObject* name = PyUnicode_FromString("caracteristique");
    PyObject* enm = PyObject_GetAttr(py_module, name);
    Py_DECREF(name);
    if (enm == nullptr)
        throw 42;
    PyObject* arglist = Py_BuildValue("(i)", static_cast<int>(in));
    PyObject* ret = PyObject_CallObject(enm, arglist);
    Py_DECREF(enm);
    Py_DECREF(arglist);
    return ret;
}

template <>
caracteristique python_to_cxx<PyObject*, caracteristique>(PyObject* in)
{
    return static_cast<caracteristique>(python_to_cxx<PyObject*, int>(in));
}

// Types de chien de débug

template<>
PyObject* cxx_to_python<PyObject*, debug_chien>(debug_chien in)
{
    PyObject* name = PyUnicode_FromString("debug_chien");
    PyObject* enm = PyObject_GetAttr(py_module, name);
    Py_DECREF(name);
    if (enm == nullptr)
        throw 42;
    PyObject* arglist = Py_BuildValue("(i)", static_cast<int>(in));
    PyObject* ret = PyObject_CallObject(enm, arglist);
    Py_DECREF(enm);
    Py_DECREF(arglist);
    return ret;
}

template <>
debug_chien python_to_cxx<PyObject*, debug_chien>(PyObject* in)
{
    return static_cast<debug_chien>(python_to_cxx<PyObject*, int>(in));
}

// Position dans le jardin, donnée par deux coordonnées.

template <>
PyObject* cxx_to_python<PyObject*, position>(position in)
{
    PyObject* tuple = PyTuple_New(2);
    PyTuple_SET_ITEM(tuple, 0, (cxx_to_python<PyObject*, int>(in.x)));
    PyTuple_SET_ITEM(tuple, 1, (cxx_to_python<PyObject*, int>(in.y)));
    return tuple;
}

template <>
position python_to_cxx<PyObject*, position>(PyObject* in)
{
    position out;
    PyObject* i;

    // Coordonnée : x
    i = PyTuple_GetItem(in, 0);
    if (i == nullptr)
        throw 42;
    out.x = python_to_cxx<PyObject*, int>(i);

    // Coordonnée : y
    i = PyTuple_GetItem(in, 1);
    if (i == nullptr)
        throw 42;
    out.y = python_to_cxx<PyObject*, int>(i);

    return out;
}

// Une plante

template <>
PyObject* cxx_to_python<PyObject*, plante>(plante in)
{
    PyObject* tuple = PyTuple_New(12);
    PyTuple_SET_ITEM(tuple, 0, (cxx_to_python<PyObject*, position>(in.pos)));
    PyTuple_SET_ITEM(tuple, 1, (cxx_to_python<PyObject*, int>(in.jardinier)));
    PyTuple_SET_ITEM(tuple, 2, (cxx_to_python<PyObject*, bool>(in.adulte)));
    PyTuple_SET_ITEM(tuple, 3, (cxx_to_python<PyObject*, bool>(in.enracinee)));
    PyTuple_SET_ITEM(tuple, 4, (cxx_to_python<PyObject*, int>(in.vie)));
    PyTuple_SET_ITEM(tuple, 5, (cxx_to_python<PyObject*, int>(in.vie_max)));
    PyTuple_SET_ITEM(tuple, 6, (cxx_to_python<PyObject*, int>(in.force)));
    PyTuple_SET_ITEM(tuple, 7, (cxx_to_python<PyObject*, int>(in.elegance)));
    PyTuple_SET_ITEM(tuple, 8, (cxx_to_python<PyObject*, int>(in.rayon_deplacement)));
    PyTuple_SET_ITEM(tuple, 9, (cxx_to_python<PyObject*, int>(in.rayon_collecte)));
    PyTuple_SET_ITEM(tuple, 10, (cxx_to_python_array(in.consommation)));
    PyTuple_SET_ITEM(tuple, 11, (cxx_to_python<PyObject*, int>(in.age)));
    PyObject* name = PyUnicode_FromString("plante");
    PyObject* cstr = PyObject_GetAttr(py_module, name);
    Py_DECREF(name);
    if (cstr == nullptr)
        throw 42;
    PyObject* ret = PyObject_CallObject(cstr, tuple);
    Py_DECREF(cstr);
    Py_DECREF(tuple);
    if (ret == nullptr)
        throw 42;
    return ret;
}

template <>
plante python_to_cxx<PyObject*, plante>(PyObject* in)
{
    plante out;
    PyObject* i;

    // Position de la plante
    i = cxx_to_python<PyObject*, int>(0);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.pos = python_to_cxx<PyObject*, position>(i);
    Py_DECREF(i);

    // Jardinier ayant planté la plante
    i = cxx_to_python<PyObject*, int>(1);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.jardinier = python_to_cxx<PyObject*, int>(i);
    Py_DECREF(i);

    // La plante est adulte
    i = cxx_to_python<PyObject*, int>(2);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.adulte = python_to_cxx<PyObject*, bool>(i);
    Py_DECREF(i);

    // La plante a déjà déjà été dépotée
    i = cxx_to_python<PyObject*, int>(3);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.enracinee = python_to_cxx<PyObject*, bool>(i);
    Py_DECREF(i);

    // Point(s) de vie restant(s) de la plante
    i = cxx_to_python<PyObject*, int>(4);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.vie = python_to_cxx<PyObject*, int>(i);
    Py_DECREF(i);

    // Point(s) de vie maximumde la plante
    i = cxx_to_python<PyObject*, int>(5);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.vie_max = python_to_cxx<PyObject*, int>(i);
    Py_DECREF(i);

    // Force de la baffe de la plante
    i = cxx_to_python<PyObject*, int>(6);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.force = python_to_cxx<PyObject*, int>(i);
    Py_DECREF(i);

    // Élégance de la plante
    i = cxx_to_python<PyObject*, int>(7);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.elegance = python_to_cxx<PyObject*, int>(i);
    Py_DECREF(i);

    // Distance maximale parcourable par la plante en creusant
    i = cxx_to_python<PyObject*, int>(8);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.rayon_deplacement = python_to_cxx<PyObject*, int>(i);
    Py_DECREF(i);

    // Rayon de collecte des ressources pour la plante
    i = cxx_to_python<PyObject*, int>(9);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.rayon_collecte = python_to_cxx<PyObject*, int>(i);
    Py_DECREF(i);

    // Quantité de ressources consommées par la plante
    i = cxx_to_python<PyObject*, int>(10);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.consommation = python_to_cxx_array<int>(i);
    Py_DECREF(i);

    // Âge de la plante
    i = cxx_to_python<PyObject*, int>(11);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.age = python_to_cxx<PyObject*, int>(i);
    Py_DECREF(i);

    return out;
}

// Représentation d'une action dans l'historique

template <>
PyObject* cxx_to_python<PyObject*, action_hist>(action_hist in)
{
    PyObject* tuple = PyTuple_New(7);
    PyTuple_SET_ITEM(tuple, 0, (cxx_to_python<PyObject*, action_type>(in.atype)));
    PyTuple_SET_ITEM(tuple, 1, (cxx_to_python<PyObject*, position>(in.position_baffante)));
    PyTuple_SET_ITEM(tuple, 2, (cxx_to_python<PyObject*, position>(in.position_baffee)));
    PyTuple_SET_ITEM(tuple, 3, (cxx_to_python<PyObject*, position>(in.position_depart)));
    PyTuple_SET_ITEM(tuple, 4, (cxx_to_python<PyObject*, position>(in.position_arrivee)));
    PyTuple_SET_ITEM(tuple, 5, (cxx_to_python<PyObject*, position>(in.position_plante)));
    PyTuple_SET_ITEM(tuple, 6, (cxx_to_python<PyObject*, caracteristique>(in.amelioration)));
    PyObject* name = PyUnicode_FromString("action_hist");
    PyObject* cstr = PyObject_GetAttr(py_module, name);
    Py_DECREF(name);
    if (cstr == nullptr)
        throw 42;
    PyObject* ret = PyObject_CallObject(cstr, tuple);
    Py_DECREF(cstr);
    Py_DECREF(tuple);
    if (ret == nullptr)
        throw 42;
    return ret;
}

template <>
action_hist python_to_cxx<PyObject*, action_hist>(PyObject* in)
{
    action_hist out;
    PyObject* i;

    // Type de l'action
    i = cxx_to_python<PyObject*, int>(0);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.atype = python_to_cxx<PyObject*, action_type>(i);
    Py_DECREF(i);

    // Position de la plante baffante (si type d'action ``action_baffer``)
    i = cxx_to_python<PyObject*, int>(1);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.position_baffante = python_to_cxx<PyObject*, position>(i);
    Py_DECREF(i);

    // Position de la plante baffée (si type d'action ``action_baffer``)
    i = cxx_to_python<PyObject*, int>(2);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.position_baffee = python_to_cxx<PyObject*, position>(i);
    Py_DECREF(i);

    // Position de la plante à déplacer (si type d'action ``action_depoter``)
    i = cxx_to_python<PyObject*, int>(3);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.position_depart = python_to_cxx<PyObject*, position>(i);
    Py_DECREF(i);

    // Position où déplacer la plante (si type d'action ``action_depoter``)
    i = cxx_to_python<PyObject*, int>(4);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.position_arrivee = python_to_cxx<PyObject*, position>(i);
    Py_DECREF(i);

    // Position de la plante  (si type d'action ``action_arroser``)
    i = cxx_to_python<PyObject*, int>(5);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.position_plante = python_to_cxx<PyObject*, position>(i);
    Py_DECREF(i);

    // Caractéristique à améliorer (si type d'action ``action_arroser``)
    i = cxx_to_python<PyObject*, int>(6);
    i = PyObject_GetItem(in, i);
    if (i == nullptr)
        throw 42;
    out.amelioration = python_to_cxx<PyObject*, caracteristique>(i);
    Py_DECREF(i);

    return out;
}


// Python native wrapper for function depoter.
// La plante creuse vers une destination donnée
static PyObject* p_depoter(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_position_depart;
    PyObject* arg_position_arrivee;
    if (!PyArg_ParseTuple(args, "OO", &arg_position_depart, &arg_position_arrivee))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, erreur>(api_depoter(python_to_cxx<PyObject*, position>(arg_position_depart), python_to_cxx<PyObject*, position>(arg_position_arrivee)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function arroser.
// Arrose une plante
static PyObject* p_arroser(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_position_plante;
    PyObject* arg_amelioration;
    if (!PyArg_ParseTuple(args, "OO", &arg_position_plante, &arg_amelioration))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, erreur>(api_arroser(python_to_cxx<PyObject*, position>(arg_position_plante), python_to_cxx<PyObject*, caracteristique>(arg_amelioration)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function baffer.
// Une plante en gifle une autre
static PyObject* p_baffer(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_position_baffante;
    PyObject* arg_position_baffee;
    if (!PyArg_ParseTuple(args, "OO", &arg_position_baffante, &arg_position_baffee))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, erreur>(api_baffer(python_to_cxx<PyObject*, position>(arg_position_baffante), python_to_cxx<PyObject*, position>(arg_position_baffee)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function debug_afficher_chien.
// Affiche le chien spécifié sur la case indiquée
static PyObject* p_debug_afficher_chien(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_pos;
    PyObject* arg_chien;
    if (!PyArg_ParseTuple(args, "OO", &arg_pos, &arg_chien))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, erreur>(api_debug_afficher_chien(python_to_cxx<PyObject*, position>(arg_pos), python_to_cxx<PyObject*, debug_chien>(arg_chien)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function plantes_jardinier.
// Renvoie la liste des plantes du jardinier
static PyObject* p_plantes_jardinier(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_jardinier;
    if (!PyArg_ParseTuple(args, "O", &arg_jardinier))
    {
        return nullptr;
    }

    try {
        return cxx_to_python_array(api_plantes_jardinier(python_to_cxx<PyObject*, int>(arg_jardinier)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function plante_sur_case.
// Renvoie la plante sur la position donnée, s'il n'y en a pas tous les champs
// sont initialisés à -1
static PyObject* p_plante_sur_case(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_pos;
    if (!PyArg_ParseTuple(args, "O", &arg_pos))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, plante>(api_plante_sur_case(python_to_cxx<PyObject*, position>(arg_pos)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function plantes_arrosables.
// Renvoie la liste des plantes du jardinier qui peuvent être arrosées
static PyObject* p_plantes_arrosables(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_jardinier;
    if (!PyArg_ParseTuple(args, "O", &arg_jardinier))
    {
        return nullptr;
    }

    try {
        return cxx_to_python_array(api_plantes_arrosables(python_to_cxx<PyObject*, int>(arg_jardinier)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function plantes_adultes.
// Renvoie la liste des plantes du jardinier qui sont adultes
static PyObject* p_plantes_adultes(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_jardinier;
    if (!PyArg_ParseTuple(args, "O", &arg_jardinier))
    {
        return nullptr;
    }

    try {
        return cxx_to_python_array(api_plantes_adultes(python_to_cxx<PyObject*, int>(arg_jardinier)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function plantes_depotables.
// Renvoie la liste des plantes du jardinier qui peuvent être dépotées
static PyObject* p_plantes_depotables(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_jardinier;
    if (!PyArg_ParseTuple(args, "O", &arg_jardinier))
    {
        return nullptr;
    }

    try {
        return cxx_to_python_array(api_plantes_depotables(python_to_cxx<PyObject*, int>(arg_jardinier)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function ressources_sur_case.
// Renvoie les ressources disponibles sur une case donnée
static PyObject* p_ressources_sur_case(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_pos;
    if (!PyArg_ParseTuple(args, "O", &arg_pos))
    {
        return nullptr;
    }

    try {
        return cxx_to_python_array(api_ressources_sur_case(python_to_cxx<PyObject*, position>(arg_pos)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function reproduction_possible.
// Vérifie si une plante à la position donnée aura suffisamment de ressources
// pour se reproduire. S'il y a déjà une plante à cette position, le calcul
// suposera qu'elle a été remplacée
static PyObject* p_reproduction_possible(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_pos;
    PyObject* arg_rayon_collecte;
    PyObject* arg_consommation;
    if (!PyArg_ParseTuple(args, "OOO", &arg_pos, &arg_rayon_collecte, &arg_consommation))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, bool>(api_reproduction_possible(python_to_cxx<PyObject*, position>(arg_pos), python_to_cxx<PyObject*, int>(arg_rayon_collecte), python_to_cxx_array<int>(arg_consommation)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function plante_reproductible.
// Vérifie si une plante à la position donnée peut se reproduire, retourne faux
// s'il n'y pas de plante à la position donnée
static PyObject* p_plante_reproductible(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_pos;
    if (!PyArg_ParseTuple(args, "O", &arg_pos))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, bool>(api_plante_reproductible(python_to_cxx<PyObject*, position>(arg_pos)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function croisement.
// Caractéristiques d'une plante résultant du croisement de plusieurs parents
// donnés. Les champs sont initialisés à -1 si aucune plante n'est donnée en
// paramètre
static PyObject* p_croisement(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_parents;
    if (!PyArg_ParseTuple(args, "O", &arg_parents))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, plante>(api_croisement(python_to_cxx_array<plante>(arg_parents)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function historique.
// Renvoie la liste des actions effectuées par l’adversaire durant son tour,
// dans l'ordre chronologique. Les actions de débug n'apparaissent pas dans
// cette liste.
static PyObject* p_historique(PyObject* /* self */, PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    {
        return nullptr;
    }

    try {
        return cxx_to_python_array(api_historique());
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function score.
// Renvoie le score du jardinier ``id_jardinier``. Renvoie -1 si le jardinier
// est invalide.
static PyObject* p_score(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_id_jardinier;
    if (!PyArg_ParseTuple(args, "O", &arg_id_jardinier))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, int>(api_score(python_to_cxx<PyObject*, int>(arg_id_jardinier)));
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function moi.
// Renvoie votre numéro de jardinier.
static PyObject* p_moi(PyObject* /* self */, PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, int>(api_moi());
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function adversaire.
// Renvoie le numéro du jardinier adverse.
static PyObject* p_adversaire(PyObject* /* self */, PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, int>(api_adversaire());
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function annuler.
// Annule la dernière action. Renvoie faux quand il n'y a pas d'action à
// annuler ce tour ci.
static PyObject* p_annuler(PyObject* /* self */, PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, bool>(api_annuler());
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function tour_actuel.
// Retourne le numéro du tour actuel.
static PyObject* p_tour_actuel(PyObject* /* self */, PyObject* args)
{
    if (!PyArg_ParseTuple(args, ""))
    {
        return nullptr;
    }

    try {
        return cxx_to_python<PyObject*, int>(api_tour_actuel());
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function afficher_erreur.
// Affiche le contenu d'une valeur de type erreur
static PyObject* p_afficher_erreur(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_v;
    if (!PyArg_ParseTuple(args, "O", &arg_v))
    {
        return nullptr;
    }

    try {
        (api_afficher_erreur(python_to_cxx<PyObject*, erreur>(arg_v)));
        Py_RETURN_NONE;
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function afficher_action_type.
// Affiche le contenu d'une valeur de type action_type
static PyObject* p_afficher_action_type(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_v;
    if (!PyArg_ParseTuple(args, "O", &arg_v))
    {
        return nullptr;
    }

    try {
        (api_afficher_action_type(python_to_cxx<PyObject*, action_type>(arg_v)));
        Py_RETURN_NONE;
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function afficher_caracteristique.
// Affiche le contenu d'une valeur de type caracteristique
static PyObject* p_afficher_caracteristique(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_v;
    if (!PyArg_ParseTuple(args, "O", &arg_v))
    {
        return nullptr;
    }

    try {
        (api_afficher_caracteristique(python_to_cxx<PyObject*, caracteristique>(arg_v)));
        Py_RETURN_NONE;
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function afficher_debug_chien.
// Affiche le contenu d'une valeur de type debug_chien
static PyObject* p_afficher_debug_chien(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_v;
    if (!PyArg_ParseTuple(args, "O", &arg_v))
    {
        return nullptr;
    }

    try {
        (api_afficher_debug_chien(python_to_cxx<PyObject*, debug_chien>(arg_v)));
        Py_RETURN_NONE;
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function afficher_position.
// Affiche le contenu d'une valeur de type position
static PyObject* p_afficher_position(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_v;
    if (!PyArg_ParseTuple(args, "O", &arg_v))
    {
        return nullptr;
    }

    try {
        (api_afficher_position(python_to_cxx<PyObject*, position>(arg_v)));
        Py_RETURN_NONE;
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function afficher_plante.
// Affiche le contenu d'une valeur de type plante
static PyObject* p_afficher_plante(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_v;
    if (!PyArg_ParseTuple(args, "O", &arg_v))
    {
        return nullptr;
    }

    try {
        (api_afficher_plante(python_to_cxx<PyObject*, plante>(arg_v)));
        Py_RETURN_NONE;
    } catch (...) {
        return nullptr;
    }
}

// Python native wrapper for function afficher_action_hist.
// Affiche le contenu d'une valeur de type action_hist
static PyObject* p_afficher_action_hist(PyObject* /* self */, PyObject* args)
{
    PyObject* arg_v;
    if (!PyArg_ParseTuple(args, "O", &arg_v))
    {
        return nullptr;
    }

    try {
        (api_afficher_action_hist(python_to_cxx<PyObject*, action_hist>(arg_v)));
        Py_RETURN_NONE;
    } catch (...) {
        return nullptr;
    }
}

// API function to register.
static PyMethodDef api_callback[] = {
    {"depoter", p_depoter, METH_VARARGS, "depoter"},
    {"arroser", p_arroser, METH_VARARGS, "arroser"},
    {"baffer", p_baffer, METH_VARARGS, "baffer"},
    {"debug_afficher_chien", p_debug_afficher_chien, METH_VARARGS, "debug_afficher_chien"},
    {"plantes_jardinier", p_plantes_jardinier, METH_VARARGS, "plantes_jardinier"},
    {"plante_sur_case", p_plante_sur_case, METH_VARARGS, "plante_sur_case"},
    {"plantes_arrosables", p_plantes_arrosables, METH_VARARGS, "plantes_arrosables"},
    {"plantes_adultes", p_plantes_adultes, METH_VARARGS, "plantes_adultes"},
    {"plantes_depotables", p_plantes_depotables, METH_VARARGS, "plantes_depotables"},
    {"ressources_sur_case", p_ressources_sur_case, METH_VARARGS, "ressources_sur_case"},
    {"reproduction_possible", p_reproduction_possible, METH_VARARGS, "reproduction_possible"},
    {"plante_reproductible", p_plante_reproductible, METH_VARARGS, "plante_reproductible"},
    {"croisement", p_croisement, METH_VARARGS, "croisement"},
    {"historique", p_historique, METH_VARARGS, "historique"},
    {"score", p_score, METH_VARARGS, "score"},
    {"moi", p_moi, METH_VARARGS, "moi"},
    {"adversaire", p_adversaire, METH_VARARGS, "adversaire"},
    {"annuler", p_annuler, METH_VARARGS, "annuler"},
    {"tour_actuel", p_tour_actuel, METH_VARARGS, "tour_actuel"},
    {"afficher_erreur", p_afficher_erreur, METH_VARARGS, "afficher_erreur"},
    {"afficher_action_type", p_afficher_action_type, METH_VARARGS, "afficher_action_type"},
    {"afficher_caracteristique", p_afficher_caracteristique, METH_VARARGS, "afficher_caracteristique"},
    {"afficher_debug_chien", p_afficher_debug_chien, METH_VARARGS, "afficher_debug_chien"},
    {"afficher_position", p_afficher_position, METH_VARARGS, "afficher_position"},
    {"afficher_plante", p_afficher_plante, METH_VARARGS, "afficher_plante"},
    {"afficher_action_hist", p_afficher_action_hist, METH_VARARGS, "afficher_action_hist"},
    {nullptr, nullptr, 0, nullptr}
};

// Initialize C module.
PyMODINIT_FUNC PyInit__api()
{
    static struct PyModuleDef apimoduledef = {
        PyModuleDef_HEAD_INIT,
        "_api",
        "API module",
        -1,
        api_callback,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    };
    return PyModule_Create(&apimoduledef);
}

// Load a Python module.
static PyObject* _import_module(const char* m)
{
    PyObject* name = PyUnicode_FromString(m);
    PyObject* mod = PyImport_Import(name);
    Py_DECREF(name);
    if (mod == nullptr)
        if (PyErr_Occurred())
        {
            PyErr_Print();
            abort();
        }
    return mod;
}

// Initialize Python VM, register API functions, and load .py file.
static void _init_python()
{
    static wchar_t empty_string[] = L"";
    static wchar_t *argv[] = { (wchar_t *) &empty_string, nullptr };

    const char* champion_path;

    champion_path = getenv("CHAMPION_PATH");
    if (champion_path == nullptr)
        champion_path = ".";

    setenv("PYTHONPATH", champion_path, 1);

    static wchar_t program_name[] = L"stechec";
    Py_SetProgramName(program_name);

    PyImport_AppendInittab("_api", PyInit__api);
    Py_Initialize();
    PySys_SetArgvEx(1, argv, 0);

    // Import a Champion module with an uppercase letter to avoid conflict with
    // champion.so
    champ_module = _import_module("Champion");
    py_module = _import_module("api");
}

// Run a Python function.
static PyObject* _call_python_function(const char* name)
{
    static bool initialized = false;

    if (!initialized)
    {
        initialized = true;
        _init_python();
    }

    PyObject *arglist, *func;
    PyObject *result = nullptr;

    func = PyObject_GetAttrString(champ_module, name);
    if (func && PyCallable_Check(func))
    {
        arglist = Py_BuildValue("()");
        result = PyEval_CallObject(func, arglist);
        Py_XDECREF(arglist);
        Py_DECREF(func);
    }
    if (result == nullptr && PyErr_Occurred())
    {
        PyErr_Print();
        abort();
    }

    return result;
}


// Functions called from Stechec to Python.

extern "C" void partie_init()
{
    PyObject* _retval = _call_python_function("partie_init");
    try {
        Py_XDECREF(_retval);
    } catch (...) {
        PyErr_Print();
        abort();
    }
}

extern "C" void jouer_tour()
{
    PyObject* _retval = _call_python_function("jouer_tour");
    try {
        Py_XDECREF(_retval);
    } catch (...) {
        PyErr_Print();
        abort();
    }
}

extern "C" void partie_fin()
{
    PyObject* _retval = _call_python_function("partie_fin");
    try {
        Py_XDECREF(_retval);
    } catch (...) {
        PyErr_Print();
        abort();
    }
}
