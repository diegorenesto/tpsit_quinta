import java.util.Scanner;

import static tools.Utility.*;

/**
 * @author Diego Renesto
 * @version 1.0
 * @since 29/09/2025
 */
public class Main {
    public static void main(String[] args) {
        // Dichiarazione oggetti e variabili
        Scanner sc = new Scanner(System.in);
        boolean uscita = false, uscitaMenu;
        String str;
        int scelta;

        // opzioni menu
        String[] opzioni = {"GESTORE TESTI", "1. Verifica Lunghezza", "2. Cerca Parola", "3. Sostituisci Parola", "4. Conta Vocali e Consonanti", "5. Inverti Frase", "6. Estrai Porzione di Testo", "7. Esci dal Menu", "8. Esci dal Programma"};

        do {
            // Menu principale
            System.out.println("Inserisci una stringa: ");
            str = sc.nextLine();

            uscitaMenu = false; // azzero per evitare errori nel rientro nel menu' (case 7)
            do {
                // Menu interno
                scelta = Menu(opzioni, sc);  // inserimento scelta

                switch (scelta) {
                    case 1 -> {
                        System.out.println("VERIFICA LUNGHEZZA");
                        System.out.println("Lunghezza: " + GestoreTesti.controllaLunghezza(str));
                    }

                    case 2 -> {
                        System.out.println("CERCA PAROLA");
                        String parola;
                        boolean presente;

                        System.out.println("Inserisci la parola da cercare:");
                        parola = sc.nextLine();
                        presente = GestoreTesti.cercaParola(str, parola);
                        if (!presente) System.out.println("Parola '" + parola + "' non presente nella stringa");
                        else System.out.println("Parola '" + parola + "' presente nella stringa");
                    }

                    case 3 -> {
                        System.out.println("SOSTITUISCI PAROLA");
                        String parolaSost, parolaNuova;

                        System.out.println("Inserisci la parola da sostituire: ");
                        parolaSost = sc.nextLine();
                        System.out.println("Inserisci la nuova parola: ");
                        parolaNuova = sc.nextLine();

                        System.out.println(GestoreTesti.sostituisciParola(str, parolaSost, parolaNuova));
                    }

                    case 4 -> {
                        System.out.println("CONTA VOCALI E CONSONANTI");
                        int vocali = GestoreTesti.contaVocali(str);
                        int consonanti = GestoreTesti.contaConsonanti(str);

                        System.out.println("Sono presenti " + vocali + " vocali");
                        System.out.println("Sono presenti " + consonanti + " consonanti");
                    }

                    case 5 -> {
                        System.out.println("INVERTI FRASE");
                        String strInvert = GestoreTesti.invertiFrase(str);
                        System.out.println(strInvert);
                    }

                    case 6 -> {
                        System.out.println("ESTRAI PORZIONE DI TESTO");
                        int index;

                        System.out.println("Inserisci l'indice di partenza:");
                        index = Integer.parseInt(sc.nextLine());
                        System.out.println(GestoreTesti.estraiPorzione(str, index));
                    }

                    case 7 -> {
                        System.out.println("TORNA AL MENU' PRINCIPALE");
                        uscitaMenu = true;
                    }

                    case 8 -> {
                        System.out.println("USCITA DAL PROGRAMMA");
                        uscitaMenu = true;
                        uscita = true; // termina entrambi i cicli
                    }
                }
            } while (!uscitaMenu);
        } while (!uscita);
    }
}