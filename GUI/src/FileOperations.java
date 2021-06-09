import java.io.*;

public class FileOperations {

    public static void writeFile(File file, String s) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(file));
            writer.write(s);
            writer.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static String readFile(File file) {
        StringBuilder text = new StringBuilder();
        try {
            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;
            boolean first = true;
            while ((line = br.readLine()) != null) {
                if (first) {
                    text.append(line);
                    first = false;
                } else {
                    text.append("\n").append(line);
                }
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        return text.toString();
    }
}
