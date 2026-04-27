package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Déclaration des méthodes natives avec des noms modifiés
    public native String getWelcomeMessage();
    public native int computeFactorial(int n);
    public native String invertText(String s);
    public native int calculateArraySum(int[] values);

    static {
        // Chargement de la bibliothèque native
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Liaison avec les composants graphiques
        TextView labelHello = findViewById(R.id.tvHello);
        TextView labelFact = findViewById(R.id.tvFact);
        TextView labelReverse = findViewById(R.id.tvReverse);
        TextView labelArray = findViewById(R.id.tvArray);

        // 1. Appel du message de bienvenue
        labelHello.setText(getWelcomeMessage());

        // 2. Calcul d'une factorielle
        int inputVal = 10;
        int resFact = computeFactorial(inputVal);
        if (resFact >= 0) {
            labelFact.setText("Résultat factorielle (" + inputVal + ") = " + resFact);
        } else {
            labelFact.setText("Erreur native : Code " + resFact);
        }

        // 3. Inversion d'une chaîne
        String original = "JNI is powerful!";
        String inverted = invertText(original);
        labelReverse.setText("Inversion : " + inverted);

        // 4. Somme d'un tableau d'entiers
        int[] data = {10, 20, 30, 40, 50};
        int total = calculateArraySum(data);
        labelArray.setText("Somme cumulée du tableau = " + total);
    }
}
