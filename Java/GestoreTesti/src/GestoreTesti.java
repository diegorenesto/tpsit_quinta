/**
 * @author Diego Renesto
 * @version 1.0
 * @since 29/09/2025
 */
public class GestoreTesti {

    /**
     * metodo controlla lunghezza di una stringa
     *
     * @param str stringa
     * @return lunghezza stringa
     */
    public static int controllaLunghezza(String str) {
        return str.length();
    }

    /**
     * metodo cerca parola in una stringa
     *
     * @param str    stringa
     * @param parola parola da cercare
     * @return boolean presente o no
     */
    public static boolean cercaParola(String str, String parola) {
        return str.contains(parola);
    }

    /**
     * metodo sostituisci parola con un'altra parola in una stringa
     *
     * @param str         stringa
     * @param parola      parola da sostituire
     * @param parolaNuova parola nuova, da sostituire al posto di 'parola'
     * @return stringa con la parola (tutte le volte che compare) sostituita
     */
    public static String sostituisciParola(String str, String parola, String parolaNuova) {
        return str.replaceAll(parola, parolaNuova);
    }

    /**
     * metodo conta vocali in una stringa
     *
     * @param str stringa
     * @return numero vocali
     */
    public static int contaVocali(String str) {
        int cont = 0;
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
                cont++;
        }
        return cont;
    }

    /**
     * metodo conta consonanti in una stringa
     *
     * @param str stringa
     * @return numero consonanti
     */
    public static int contaConsonanti(String str) {
        int cont = 0;
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == ' '))
                cont++;
        }
        return cont;
    }

    /**
     * metodo che inverte una stringa
     *
     * @param str stringa
     * @return stringa invertita
     */
    public static String invertiFrase(String str) {
        String strInvert = "";
        for (int i = str.length() - 1; i >= 0; i--) {
            strInvert += str.charAt(i);
        }
        return strInvert;
    }

    /**
     * metodo che estrae una porzione di testo in una stringa
     *
     * @param str        stringa
     * @param beginIndex indice di partenza
     * @return porzione di testo estratta
     */
    public static String estraiPorzione(String str, int beginIndex) {
        return str.substring(beginIndex); // estraggo una porzione di testo a partire da beginIndex
    }
}
