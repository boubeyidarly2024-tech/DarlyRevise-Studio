#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

vector<string> splitSentences(const string& text) {
    vector<string> sentences;
    string current;
    for (char c : text) {
        current += c;
        if (c == '.' || c == '!' || c == '?' || c == '\n') {
            string part = trim(current);
            if (part.size() > 15) sentences.push_back(part);
            current.clear();
        }
    }
    string last = trim(current);
    if (last.size() > 15) sentences.push_back(last);
    return sentences;
}

string makeSummary(const string& chapter, const string& subject, const string& course) {
    string title = chapter.empty() ? "Chapitre à préciser" : chapter;
    stringstream out;
    out << "RÉSUMÉ DE RÉVISION\n";
    out << title << "\n";
    if (!subject.empty()) out << "Matière : " << subject << "\n";
    out << "\n";

    if (course.empty()) {
        out << "Ajoute le contenu du cours pour obtenir une synthèse.\n";
        out << "Méthode conseillée : relève les définitions, les notions clés, "
               "les étapes importantes et les exemples.";
        return out.str();
    }

    vector<string> sentences = splitSentences(course);
    out << "Points à retenir :\n";
    if (sentences.empty()) {
        out << "- Relis le texte et repère les idées principales.\n";
        out << "- Identifie les mots-clés et les définitions.\n";
    } else {
        size_t limit = min<size_t>(sentences.size(), 5);
        for (size_t i = 0; i < limit; ++i)
            out << "• " << sentences[i] << "\n";
    }
    out << "\nConseil : vérifie chaque point avec ton support de cours.";
    return out.str();
}

string makeQuiz(const string& chapter, const string& subject, const string& course) {
    string title = chapter.empty() ? "Révision générale" : chapter;
    stringstream out;
    out << "QUIZ D'ENTRAÎNEMENT\n" << title << "\n";
    if (!subject.empty()) out << "Matière : " << subject << "\n";
    out << "\n";
    vector<string> sentences = splitSentences(course);
    out << "1. Explique avec tes propres mots le thème principal du chapitre.\n";
    out << "2. Quelles sont les trois notions les plus importantes à retenir ?\n";
    out << "3. Donne un exemple concret qui illustre le cours.\n";
    if (!sentences.empty()) {
        out << "4. Que signifie cette idée dans ton cours : « " << sentences[0] << " » ?\n";
    } else {
        out << "4. Quelle définition ou formule dois-tu absolument connaître ?\n";
    }
    out << "5. Quelle question aimerais-tu poser à ton enseignant ?\n\n";
    out << "Auto-évaluation : attribue-toi 1 point par réponse claire, puis reprends les notions difficiles.";
    return out.str();
}

string makePlan(const string& chapter, const string& subject, const string& course) {
    stringstream out;
    out << "PLAN DE RÉVISION\n";
    out << "Chapitre : " << (chapter.empty() ? "À définir" : chapter) << "\n";
    if (!subject.empty()) out << "Matière : " << subject << "\n";
    out << "\nSéance de 30 minutes :\n";
    out << "1. 5 min — Parcourir le cours et repérer les titres.\n";
    out << "2. 10 min — Résumer les notions essentielles.\n";
    out << "3. 10 min — Répondre au quiz sans regarder le cours.\n";
    out << "4. 5 min — Corriger et noter les points à revoir.\n";
    if (course.empty()) out << "\nAjoute ton cours pour personnaliser davantage la séance.";
    else out << "\nPense à vérifier les notions du plan dans ton support officiel.";
    return out.str();
}

int main(int argc, char* argv[]) {
    string action = argc > 1 ? argv[1] : "summary";
    string chapter = argc > 2 ? argv[2] : "";
    string subject = argc > 3 ? argv[3] : "";

    string course, line;
    while (getline(cin, line)) {
        if (!course.empty()) course += "\n";
        course += line;
    }

    if (action == "summary") cout << makeSummary(chapter, subject, course);
    else if (action == "quiz") cout << makeQuiz(chapter, subject, course);
    else if (action == "plan") cout << makePlan(chapter, subject, course);
    else {
        cerr << "Action non reconnue.";
        return 2;
    }
    return 0;
}
