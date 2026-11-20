from flask import Flask, render_template, request, jsonify
from pathlib import Path
import subprocess

BASE_DIR = Path(__file__).resolve().parent
ENGINE = BASE_DIR / "engine" / ("DarlyEngine.exe" if __import__("os").name == "nt" else "DarlyEngine")

app = Flask(__name__)

@app.get("/")
def home():
    return render_template("index.html")

@app.post("/api/generate")
def generate():
    data = request.get_json(silent=True) or {}
    action = str(data.get("action", "summary"))
    chapter = str(data.get("chapter", "")).strip()
    subject = str(data.get("subject", "")).strip()
    course = str(data.get("course", "")).strip()

    if action not in {"summary", "quiz", "plan"}:
        return jsonify({"error": "Action inconnue."}), 400
    if not chapter and not course:
        return jsonify({"error": "Indique un chapitre ou colle le contenu du cours."}), 400
    if not ENGINE.exists():
        return jsonify({
            "error": "Le moteur C++ est introuvable. Compile d'abord le projet avec Code::Blocks. Consulte README.md."
        }), 500

    try:
        completed = subprocess.run(
            [str(ENGINE), action, chapter, subject],
            input=course,
            text=True,
            encoding="utf-8",
            capture_output=True,
            timeout=10,
            cwd=str(BASE_DIR)
        )
        if completed.returncode != 0:
            return jsonify({"error": "Erreur du moteur C++ : " + completed.stderr}), 500
        return jsonify({"result": completed.stdout.strip()})
    except subprocess.TimeoutExpired:
        return jsonify({"error": "Le moteur C++ a mis trop de temps à répondre."}), 504
    except Exception as exc:
        return jsonify({"error": f"Impossible de lancer le moteur C++ : {exc}"}), 500

if __name__ == "__main__":
    import os
    app.run(host="0.0.0.0", port=int(os.environ.get("PORT", "5000")), debug=False)
