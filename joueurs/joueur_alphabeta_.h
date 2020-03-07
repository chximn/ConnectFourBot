#pragma once
#include "joueur.h"
#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <utility>

#define infinity 2147483647
#define ALPHA_BETA_DEPTH 1
#define ALPHA_MAX_HAUTEUR 6
#define ALPHA_MAX_LARGEUR 7

#define STATE_MAXIMIZING_PLAYER_WIN 1
#define STATE_MINIMIZING_PLAYER_WIN 2
#define STATE_DRAW 0

using variation_stack = std::stack<int>;
using eval_var = std::pair<int, variation_stack>;

class Variation {
    private:
        variation_stack _stack;

    public:
        static bool activated;

        int pop();
        void load(std::stack<int> const & s);
        void step();
        int peek();
};

class Observateur {
private:
    int _nodes;
    int _alpha_cutoffs;
    int _beta_cutoffs;

public:
    void add_node();
    void add_alpha_cutoff();
    void add_beta_cutoff();

    void reset();
    void show();
};

class VirtualGame {
private:
    std::vector<int> _plays;
    bool _map[ALPHA_MAX_LARGEUR][ALPHA_MAX_HAUTEUR];
    int  _heights[ALPHA_MAX_HAUTEUR];
    int  _state;

    void update_plays();

public:
    VirtualGame(Plateau const & p);

    int mask(int x, int y);
    int get_state() { return _state; }
    std::vector<int> const & get_plays();
    std::vector<int> get_plays(Variation &);
    void play(int x, bool maximizingPlayer);
    void unplay(int x);
    bool ended();
};

class Joueur_AlphaBeta_ : public Joueur
{

private:
    std::unique_ptr<VirtualGame> vgame;
    Observateur observateur;
    Variation variation;

public:
    Joueur_AlphaBeta_(std::string nom, bool joueur);
    char nom_abbrege() const override;

    void recherche_coup(Jeu, int & c) override;

    void init_vgame(Jeu &);
    eval_var alphabeta(int depth, int alpha, int beta, bool maximizingPlayer);
    int evaluation(bool maximizingPlayer);
};
