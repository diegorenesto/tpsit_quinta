package tools;

import java.util.Scanner;

public final class Utility {
    private Utility() {
        throw new AssertionError("Utility class - non istanziabile");
    }


    public static void clrScr() {
        try {
            if (isWindows()) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            } else {
                // prova comando di sistema solo se TERM è valido; evita messaggi quando TERM non è settato
                String term = System.getenv("TERM");
                boolean canUseClear = term != null && !term.isEmpty() && !"dumb".equalsIgnoreCase(term);
                if (canUseClear) {
                    try {
                        ProcessBuilder pb = new ProcessBuilder("clear");
                        pb.redirectErrorStream(true);
                        pb.start().waitFor(); // non eredita IO: sopprime eventuali messaggi
                    } catch (Exception ignored) {
                        // ignora ed usa fallback ANSI
                    }
                }
                // Fallback ANSI
                System.out.print("\033[H\033[2J");
                System.out.flush();
            }
        } catch (Exception e) {
            // Fallback finale ANSI anche su Windows nel caso di problemi
            System.out.print("\033[H\033[2J");
            System.out.flush();
        }
    }

    private static boolean isWindows() {
        String os = System.getProperty("os.name");
        return os != null && os.toLowerCase().contains("win");
    }


    public static void Wait(int attesa) {
        try {
            if (attesa > 0) Thread.sleep(attesa);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public static int Menu(String opzioni[], Scanner tastiera) {
        int scelta;

        do {
            clrScr();
            System.out.println("------------------");
            System.out.println(opzioni[0]);
            System.out.println("------------------");
            for (int i = 1; i < opzioni.length; i++) {
                System.out.println("[" + i + "]" + " " + opzioni[i]);
            }
            try {
                scelta = Integer.parseInt(tastiera.nextLine());
            } catch (NumberFormatException ex) {
                scelta = -1;
            }
            if ((scelta < 1) || (scelta > opzioni.length - 1)) {
                System.out.println("Opzione Sbagliata");
                Wait(2000);
            }
        } while ((scelta < 1) || (scelta > opzioni.length - 1));
        return scelta;
    }
}