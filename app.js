let selectedAction = "summary";
const buttons = document.querySelectorAll(".tool-card");
const generateButton = document.getElementById("generate");
const resultBox = document.getElementById("result");
const titleBox = document.getElementById("output-title");
const messageBox = document.getElementById("message");
const copyButton = document.getElementById("copy");

const titles = {
  summary: "Résumé de révision",
  quiz: "Quiz d'entraînement",
  plan: "Plan de révision"
};

buttons.forEach(button => {
  button.addEventListener("click", () => {
    buttons.forEach(item => item.classList.remove("selected"));
    button.classList.add("selected");
    selectedAction = button.dataset.action;
  });
});

generateButton.addEventListener("click", async () => {
  const payload = {
    action: selectedAction,
    chapter: document.getElementById("chapter").value.trim(),
    subject: document.getElementById("subject").value.trim(),
    course: document.getElementById("course").value.trim()
  };

  generateButton.disabled = true;
  generateButton.querySelector("span:first-child").textContent = "Génération en cours…";
  messageBox.classList.remove("error");
  messageBox.textContent = "Le serveur Python transmet la demande au moteur C++…";

  try {
    const response = await fetch("/api/generate", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify(payload)
    });
    const data = await response.json();
    if (!response.ok) throw new Error(data.error || "Une erreur est survenue.");

    titleBox.textContent = titles[selectedAction];
    resultBox.textContent = data.result;
    copyButton.disabled = false;
    messageBox.textContent = "Résultat généré par le prototype. Vérifie les informations avec ton cours.";
  } catch (error) {
    titleBox.textContent = "Impossible de générer le résultat";
    resultBox.textContent = error.message;
    messageBox.textContent = "Vérifie que le serveur Python et le moteur C++ sont lancés.";
    messageBox.classList.add("error");
    copyButton.disabled = true;
  } finally {
    generateButton.disabled = false;
    generateButton.querySelector("span:first-child").textContent = "Générer mon support";
  }
});

copyButton.addEventListener("click", async () => {
  try {
    await navigator.clipboard.writeText(resultBox.textContent);
    copyButton.textContent = "Copié !";
    setTimeout(() => copyButton.textContent = "Copier", 1400);
  } catch {
    messageBox.textContent = "La copie automatique n'est pas disponible dans ce navigateur.";
  }
});
