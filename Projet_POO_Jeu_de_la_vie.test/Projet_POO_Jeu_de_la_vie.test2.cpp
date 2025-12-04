#include "pch.h"
#include "CppUnitTest.h"

#include <fstream>
#include <sstream>
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
    TEST_CLASS(PatternBasedTest)
    {
        // petite fonction utilitaire pour lire un fichier entier dans une std::string
        static std::string ReadAll(const std::string& path)
        {
            std::ifstream f(path);
            if (!f.is_open())
                throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);

            std::ostringstream ss;
            ss << f.rdbuf();
            return ss.str();
        }

        // helper pour comparer le contenu de deux fichiers texte
        static void AssertFilesEqual(const std::string& expectedPath,
            const std::string& actualPath,
            const wchar_t* message)
        {
            std::string expected = ReadAll(expectedPath);
            std::string actual = ReadAll(actualPath);

            // conversion en wstring pour utiliser Assert::AreEqual
            std::wstring wexp(expected.begin(), expected.end());
            std::wstring wact(actual.begin(), actual.end());

            Assert::AreEqual(wexp.c_str(), wact.c_str(), message);
        }

    public:

        TEST_METHOD(Test_Blinker_ApresUneIteration)
        {
            const std::string inputFile = "patterns/blinker_init.txt";
            const std::string expectedFile = "patterns/blinker_after1.txt";
            const std::string outDirBase = "patterns/out_blinker";
            const std::string outPath = outDirBase + "/iter_1.txt";

            // Charger l'état initial du blinker
            Jeu jeu(1, 1, std::make_unique<RegleC>());
            try {
                jeu.chargerDepuisFichier(inputFile);
            }
            catch (const std::exception& e) {
                Assert::Fail((L"Échec lecture fichier: "
                    + std::wstring(e.what(), e.what() + strlen(e.what()))).c_str());
            }

            // Une seule mise à jour
            jeu.mettreAJour();

            // Sauvegarde de l'état obtenu
            try {
                jeu.sauvegarderDansFichier(outPath);
            }
            catch (const std::exception& e) {
                Assert::Fail((L"Échec écriture fichier: "
                    + std::wstring(e.what(), e.what() + strlen(e.what()))).c_str());
            }

            // Comparaison avec le fichier attendu
            AssertFilesEqual(expectedFile, outPath,
                L"Le blinker après 1 itération ne correspond pas à l'état attendu.");
        }
    };
}
