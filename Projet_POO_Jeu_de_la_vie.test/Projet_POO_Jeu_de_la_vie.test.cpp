#include "pch.h"
#include "CppUnitTest.h"

#include <vector>
#include <fstream>

#include "../Jeu.h"
#include "../RegleC.h"
#include "../Cellule.h" 
#include "../Grille.h"
#include "../CelluleMorte.h" 
#include "../CelluleVivante.h"
#include "../Regle.h"
#include <memory>
#include "../Jeu.cpp"
#include "../RegleC.cpp"
#include "../Cellule.cpp" 
#include "../Grille.cpp"
#include "../CelluleMorte.cpp" 
#include "../CelluleVivante.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetPOOJeudelavietest
{
  
    TEST_CLASS(TestGrilleSimple)
    {
    public:
        TEST_METHOD(Blockstill_life) // Cette grille doit rester stable
        {
            std::vector<std::vector<int>> blockinitial = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            };

            std::vector<std::vector<int>> blockattendu = blockinitial;
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
            for (size_t i = 0; i < blockattendu.size(); ++i)
            {
                Assert::AreEqual(blockattendu[i].size(), matOut[i].size());
                for (size_t j = 0; j < blockattendu[i].size(); ++j)
                {
                    Assert::AreEqual(blockattendu[i][j], matOut[i][j]);
                }
            }
        }
    };

   
    TEST_CLASS(vérification_enregistrement_fichier)
    {
    public:
        static const int iter = 5;

        TEST_METHOD(Test_SaveAfterNIterations)
        {
            const std::string inputFile = "testfichier.txt";
            const std::string outDirBase = "testfichier_out";
            const std::string outPath = outDirBase + "/iter_" + std::to_string(iter) + ".txt";

            // Création du jeu et chargement du fichier
            Jeu jeu(1, 1, std::make_unique<RegleC>());
            try {
                jeu.chargerDepuisFichier(inputFile);
            }
            catch (const std::exception& e) {
                Assert::Fail((L"Échec lecture fichier: " + std::wstring(e.what(), e.what() + strlen(e.what()))).c_str());
            }

        
            for (int i = 0; i < iter; ++i) {
                jeu.mettreAJour();
            }

            
            try {
                jeu.sauvegarderDansFichier(outPath);
            }
            catch (const std::exception& e) {
                Assert::Fail((L"Échec écriture fichier: " + std::wstring(e.what(), e.what() + strlen(e.what()))).c_str());
            }

            // Vérifier que le fichier de sortie existe et n'est pas vide
            std::ifstream f(outPath);
            Assert::IsTrue(f.is_open(), L"Le fichier de sortie n'a pas été créé.");
            f.seekg(0, std::ios::end);
            Assert::IsTrue(f.tellg() > 0, L"Le fichier de sortie est vide.");
        }
    };
    

    
}
