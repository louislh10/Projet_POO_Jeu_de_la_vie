
#include "pch.h"
#include "CppUnitTest.h"

#include <fstream>
#include <string>
#include <memory>

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

namespace ProjetPOOJeudelavietest
{
    static const int ITERATIONS = 5; 

    TEST_CLASS(SimpleFileBasedTest)
    {
    public:

        TEST_METHOD(Test_SaveAfterNIterations)
        {
            const std::string inputFile = "testfichier.txt"; 
            const std::string outDirBase = "testfichier_out";
            const std::string outPath = outDirBase + "/iter_" + std::to_string(ITERATIONS) + ".txt";

           // on charge le jeu
            Jeu jeu(1, 1, std::make_unique<RegleC>());
            try {
                jeu.chargerDepuisFichier(inputFile);
            }
            catch (const std::exception& e) {
                Assert::Fail((L"Échec lecture fichier: " + std::wstring(e.what(), e.what() + strlen(e.what()))).c_str());
            }

            
            for (int i = 0; i < ITERATIONS; ++i) {
                jeu.mettreAJour();
            }
            try {
                jeu.sauvegarderDansFichier(outPath);
            }
            catch (const std::exception& e) {
                Assert::Fail((L"Échec écriture fichier: " + std::wstring(e.what(), e.what() + strlen(e.what()))).c_str());
            }
// maintenant, testons que le fichier de sortie existe et n'est pas vide
            std::ifstream f(outPath);
            Assert::IsTrue(f.is_open(), L"Le fichier de sortie n'a pas été créé.");
            f.seekg(0, std::ios::end);
            Assert::IsTrue(f.tellg() > 0, L"Le fichier de sortie est vide.");
            f.close();
        }
    };
}