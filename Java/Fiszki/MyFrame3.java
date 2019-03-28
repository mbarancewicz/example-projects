import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;

public class MyFrame3 extends JFrame{
    private JTextField translateField;
    private JTextField keyField;
    private JTextField valueField;
    private JLabel wordToGuess;
    private JLabel keyLabel;
    private JLabel valueLabel;
    private JLabel result;
    private JButton checkButton;
    private JButton resetButton;
    private JButton addButton;
    private JButton langButton;
    private  Map<String, String> dictionary = new HashMap<String, String>();
    Random random = new Random();

    public MyFrame3() {
        super("Program do nauki jezyka");
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500,300);
        //wysrodkowanie
        int x = (screenSize.width - getWidth()) / 2;
        int y = (screenSize.height - getHeight()) / 2;
        setLocation(x, y);
        setLayout(new GridLayout(7,2));
        add(new JLabel("Slowo: "));
        wordToGuess = new JLabel("");
        add(wordToGuess);
        add(new JLabel("Tlumaczenie: "));
        translateField = new JTextField();
        add(translateField);
        JLabel fill = new JLabel("");
        add(fill);
        result = new JLabel("");
        add(result);

        //testowy slownik
        dictionary.put("kot", "cat");
        dictionary.put("pies", "dog");
        dictionary.put("papuga", "parrot");
        dictionary.put("wilk", "wolf");
        dictionary.put("ryba", "fish");
        dictionary.put("waz", "snake");
        dictionary.put("wielblad", "camel");

        checkButton = new JButton("Sprawdz");
        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent checkButtonEvent) {
                if(dictionary.size() == 0) {
                    result.setText("Brak slow w slowniku!");
                }
                else if(wordToGuess.getText().equals("")) {
                    result.setText("Najpierw wylosuj slowo");
                }
                else if(translateField.getText().equals("")) {
                    result.setText("ZLE");
                }
                else if (dictionary.get(wordToGuess.getText()).equals(translateField.getText())) {
                    result.setText("DOBRZE");
                }
                else {
                    result.setText("ZLE");
                }
            }
        });
        add(checkButton);

        resetButton = new JButton("Nastepne slowo");
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent resetButtonEvent) {
                if(dictionary.size() == 0) {
                    result.setText("Brak slow w slowniku!");
                }
                else {
                    translateField.setText("");
                    result.setText("");
                    List<String> keys = new ArrayList<String>(dictionary.keySet());
                    String randomKey = keys.get(random.nextInt(keys.size()));
                    wordToGuess.setText(randomKey);
                }
            }
        });
        add(resetButton);

        addButton = new JButton("Dodaj slowo");
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent addButtonEvent) {
                if(keyField.getText().equals("") || valueField.getText().equals("")) {
                    wordToGuess.setText("");
                    translateField.setText("");
                    keyField.setText("");
                    valueField.setText("");
                    result.setText("Blad dodawania slowa");
                }
                else {
                    for(Map.Entry<String, String> entry : dictionary.entrySet()) {
                        if(entry.getKey().equals(keyField.getText())) {
                            keyField.setText("");
                            valueField.setText("");
                            wordToGuess.setText("");
                            translateField.setText("");
                            result.setText("Slowo znajduje sie w slowniku");
                            return;
                        }
                    }

                    dictionary.put(keyField.getText(), valueField.getText());
                    keyField.setText("");
                    valueField.setText("");
                    wordToGuess.setText("");
                    translateField.setText("");
                    result.setText("Pomyslnie dodano slowo");
                }
            }
        });
        add(addButton);

        langButton = new JButton("Zmien jezyk");
        langButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent langButtonEvent) {
                wordToGuess.setText("");
                translateField.setText("");
                Map<String, String> dictionaryReverse = new HashMap<String, String>();
                for(Map.Entry<String, String> entry : dictionary.entrySet()) {
                    dictionaryReverse.put(entry.getValue(), entry.getKey());
                }
                dictionary.clear();
                dictionary.putAll(dictionaryReverse);
                if(keyLabel.getText().equals("Po polsku:")) {
                    keyLabel.setText("Po angielsku:");
                    valueLabel.setText("Po polsku:");
                }
                else {
                    keyLabel.setText("Po polsku:");
                    valueLabel.setText("Po angielsku:");
                }
                result.setText("Zmieniono jezyk");
            }
        });
        add(langButton);

        keyLabel = new JLabel("Po polsku:");
        add(keyLabel);
        keyField = new JTextField();
        add(keyField);
        valueLabel = new JLabel("Po angielsku:");
        add(valueLabel);
        valueField = new JTextField();
        add(valueField);



        setVisible(true);
    }

}
