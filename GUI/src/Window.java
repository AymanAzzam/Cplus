import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;


class Window extends JFrame implements ActionListener {
    private JPanel leftPanel;
    private JPanel rightPanel;
    private JTextPane sourceTextArea;
    private JButton browseButton, compileButton, clearButton;
    private JTextPane outputTextArea;
    private String[] outputText = new String[3];
    private JButton[] tabsButtons;
    private int currentTabIndex = 0;
    private JFileChooser fileChooser = new JFileChooser();
    private static final boolean isWindows = System.getProperty("os.name").contains("Windows");

    Window() {
        setTitle("C+ Compiler");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(850, 600);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(1, 2));
        buildLeftPanel();
        buildRightPanel();
        add(leftPanel);
        add(rightPanel);
    }

    private void buildLeftPanel() {
        sourceTextArea = new JTextPane();
        sourceTextArea.setFont(new Font("monospaced", Font.PLAIN, 12));
        sourceTextArea.setText("int main() {\n" +
                "    return 0;\n" +
                "}");
        leftPanel = new JPanel(new BorderLayout());
        leftPanel.add(putLineNumbers(sourceTextArea), BorderLayout.CENTER);
        leftPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
        JPanel bottomPanel = new JPanel(new FlowLayout());
        browseButton = new JButton("Browse");
        compileButton = new JButton("Compile");
        clearButton = new JButton("Clear");
        bottomPanel.add(browseButton);
        bottomPanel.add(compileButton);
        bottomPanel.add(clearButton);
        browseButton.addActionListener(this);
        compileButton.addActionListener(this);
        clearButton.addActionListener(this);
        leftPanel.add(bottomPanel, BorderLayout.PAGE_END);
    }

    private void buildRightPanel() {
        outputTextArea = new JTextPane();
        outputTextArea.setFont(new Font("monospaced", Font.PLAIN, 12));
        outputTextArea.setEditable(false);
        rightPanel = new JPanel(new BorderLayout());
        rightPanel.add(putLineNumbers(outputTextArea), BorderLayout.CENTER);
        rightPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
        JPanel bottomPanel = new JPanel(new FlowLayout());
        JButton quadButton = new JButton("Quadruples");
        JButton symbolButton = new JButton("Symbols");
        JButton logsButton = new JButton("Logs");
        tabsButtons = new JButton[]{quadButton, symbolButton, logsButton};
        for (JButton button : tabsButtons) {
            bottomPanel.add(button);
            button.addActionListener(this);
        }
        rightPanel.add(bottomPanel, BorderLayout.PAGE_END);
        switchTab(currentTabIndex);
    }

    private void switchTab(int index) {
        tabsButtons[currentTabIndex].setEnabled(true);
        tabsButtons[index].setEnabled(false);
        outputTextArea.setText(outputText[index]);
        outputTextArea.setCaretPosition(0);
        currentTabIndex = index;
    }

    private JScrollPane putLineNumbers(JTextPane textPane) {
        JScrollPane scrollPane = new JScrollPane(textPane);
        TextLineNumber tln = new TextLineNumber(textPane);
        scrollPane.setRowHeaderView(tln);
        return scrollPane;
    }

    private void compile() {
        String source = sourceTextArea.getText();
        FileOperations.writeFile(new File("source.cp"), source);
        try {
            if (isWindows) {
                new ProcessBuilder("cplus.exe", "source.cp").start().waitFor();
            } else {
                new ProcessBuilder("./cplus", "source.cp").start().waitFor();
            }
            outputText[0] = FileOperations.readFile(new File("quad.txt"));
            outputText[1] = FileOperations.readFile(new File("table.txt"));
            outputText[2] = FileOperations.readFile(new File("log.txt"));
            switchTab(0);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void browse() {
        int rVal = fileChooser.showOpenDialog(this);
        if (rVal == JFileChooser.APPROVE_OPTION) {
            sourceTextArea.setText(FileOperations.readFile(fileChooser.getSelectedFile()));
            sourceTextArea.setCaretPosition(0);
            sourceTextArea.revalidate();
        }
    }

    private void clear() {
        for (int i = 0; i < 3; i++)
            outputText[i] = "";
        sourceTextArea.setText("");
        switchTab(currentTabIndex);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == tabsButtons[0])
            switchTab(0);
        else if (e.getSource() == tabsButtons[1])
            switchTab(1);
        else if (e.getSource() == tabsButtons[2])
            switchTab(2);
        else if (e.getSource() == compileButton)
            compile();
        else if (e.getSource() == clearButton)
            clear();
        else if (e.getSource() == browseButton)
            browse();
    }
}
