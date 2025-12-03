#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

#include "../Jeu.h"
#include "../Jeu.cpp"
#include "../RegleC.h"
#include "../RegleC.cpp"
#include "../Cellule.h" 
#include "../Cellule.cpp" 
#include "../Grille.h"
#include "../Grille.cpp"
#include "../CelluleMorte.h" 
#include "../CelluleMorte.cpp"
#include "../CelluleVivante.h"
#include "../CelluleVivante.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetPOOJeudelaviedesLouistest
{
    TEST_CLASS(TestGrilleSimple)
    {
    public:

        TEST_METHOD(Blockstill_life)// cette grile doit quoi qu'il arrive ne pas bouger 
        {
            std::vector<std::vector<int>> blockinitial = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            };

            std::vector<std::vector<int>> blockattendu = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            };

            const int iter = 5;

            int h = static_cast<int>(blockinitial.size());
            int w = static_cast<int>(blockinitial[0].size());

            Grille g(w, h);           
            g.initialiserDepuisMatrice(blockinitial);

            RegleC rule;

            for (int i = 0; i < iter; ++i)
                g.appliquerRegle(rule);

            std::vector<std::vector<int>> matOut = g.convertirEnMatrice();

            Assert::AreEqual(blockattendu.size(), matOut.size()); 

			for (size_t i = 0; i < blockattendu.size(); ++i) //permet de comparer chaque ligne
            {
                Assert::AreEqual(blockattendu[i].size(), matOut[i].size());

				for (size_t j = 0; j < blockattendu[i].size(); ++j) //permet de comparer chaque élément de la ligne
                {
                    Assert::AreEqual(blockattendu[i][j], matOut[i][j]);
                }
            }

        }
    };
}
