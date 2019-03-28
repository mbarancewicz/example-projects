import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class Fridge extends JFrame {
    private ArrayList<Product> listOfProducts = new ArrayList<Product>();

    private JTextField productType;
    private JTextField productBuyDate;
    private JTextField productExpDate;
    private JTextField productDaysToExp;
    private JTextField productOpen;

    private JButton addButton;
    private JButton showOpenedButton;
    private JButton showExpButton;

    public Fridge() {
        super("Lodowka");
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 300);

        Calendar calendar = new GregorianCalendar(2013, 11, 1);
        Calendar calendar2 = new GregorianCalendar(2019, 1, 10);
        Product ser = new Product("ser", calendar, new GregorianCalendar(2019, 0, 1),false);
        Product ciasto = new Product("ciasto", calendar, new GregorianCalendar(2019, 1, 13),true);
        Product jogurt = new Product("jogurt", calendar, new GregorianCalendar(2019, 1, 14),true);
        Product szynka = new Product("szynka", calendar, new GregorianCalendar(2020, 2, 14),false);
        listOfProducts.add(ser);
        listOfProducts.add(ciasto);
        listOfProducts.add(jogurt);
        listOfProducts.add(szynka);

        int x = (screenSize.width - getWidth()) / 2;
        int y = (screenSize.height - getHeight()) / 2;
        setLocation(x, y);
        setLayout(new GridLayout(6,2));
        add(new JLabel("Typ produktu:"));
        productType = new JTextField();
        add(productType);
        add(new JLabel("Data zakupu (YYYY MM DD):"));
        productBuyDate = new JTextField();
        add(productBuyDate);
        add(new JLabel("Temin przedatnosci: (YYYY MM DD)"));
        productExpDate = new JTextField();
        add(productExpDate);
        add(new JLabel("Produkt otwarty? (T/N):"));
        productOpen = new JTextField();
        add(productOpen);

        addButton = new JButton("Dodaj");
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent addProductEvent) {
                if(productType.getText().isEmpty() || productBuyDate.getText().isEmpty()
                    || productExpDate.getText().isEmpty() || productOpen.getText().isEmpty()) {
                    JOptionPane.showMessageDialog(new JFrame(), "Puste pole");
                }
                else if(!productBuyDate.getText().matches("^\\d{4} \\d{2} \\d{2}")
                        || !productExpDate.getText().matches("^\\d{4} \\d{2} \\d{2}")) {
                    JOptionPane.showMessageDialog(new JFrame(), "Niepoprawna data, podaj w formacie YYYY MM DD");
                }
                else if(!productOpen.getText().toUpperCase().matches("^[TN]{1}")) {
                    JOptionPane.showMessageDialog(new JFrame(), "Niepoprawna zawartosc pola Otwarte: (T/N)");
                }
                else {
                    int productBuyDateYear = Integer.parseInt(productBuyDate.getText().substring(0,4));
                    int productBuyDateMonth = Integer.parseInt(productBuyDate.getText().substring(5,7)) - 1;
                    int productBuyDateDay = Integer.parseInt(productBuyDate.getText().substring(8,10));
                    int productExpDateYear = Integer.parseInt(productExpDate.getText().substring(0,4));
                    int productExpDateMonth = Integer.parseInt(productExpDate.getText().substring(5,7)) - 1;
                    int productExpDateDay = Integer.parseInt(productExpDate.getText().substring(8,10));

                    if((productBuyDateMonth > 11 || productBuyDateMonth < 0 || productBuyDateDay > 31 || productBuyDateDay == 0)
                        || (productExpDateMonth > 11 || productExpDateMonth < 0 || productExpDateDay > 31 || productExpDateDay == 0)) {
                        JOptionPane.showMessageDialog(new JFrame(), "Niepoprawna data, podaj w formacie YYYY MM DD");
                    }
                    else {
                        Calendar buyDate = new GregorianCalendar(productBuyDateYear, productBuyDateMonth, productBuyDateDay);
                        Calendar expDate = new GregorianCalendar(productExpDateYear, productExpDateMonth, productExpDateDay);
                        boolean open = false;
                        if(productOpen.getText().toUpperCase().equals("T")) {
                            open = true;
                        }
                        Product product = new Product(productType.getText(), buyDate, expDate, open);
                        listOfProducts.add(product);
                        JOptionPane.showMessageDialog(new JFrame(), "Dodano produkt do lodowki");
                    }
                    // 2013 02 21
                }
            }
        });
        add(addButton);

        showOpenedButton = new JButton("Pokaz otwarte produkty");
        showOpenedButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent showOpenedEvent) {
                if(listOfProducts.isEmpty()) {
                    JOptionPane.showMessageDialog(new JFrame(), "Lista przedmiotow jest pusta");
                }
                else {
                    String selectedProducts = new String();
                    selectedProducts += "Typ         | Data zakupu    | Data przydatnosci | Stan produktu \n";
                    boolean empty = true;
                    for(Product product : listOfProducts) {
                        if(product.getState()) {
                            selectedProducts += product + "\n";
                            empty = false;
                        }
                    }
                    if(empty ) {
                        JOptionPane.showMessageDialog(new JFrame(), "Wszystkie produkty sa zamkniete");
                    }
                    else {
                        JOptionPane.showMessageDialog(new JFrame(), selectedProducts);
                    }
                }
            }
        });
        add(showOpenedButton);

        productDaysToExp = new JTextField();
        add(productDaysToExp);

        showExpButton = new JButton("Produkty z krotka data");
        showExpButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent showExpEvent) {
                if(listOfProducts.isEmpty()) {
                    JOptionPane.showMessageDialog(new JFrame(), "Lista przedmiotow jest pusta");
                }
                else if(productDaysToExp.getText().equals("")) {
                    JOptionPane.showMessageDialog(new JFrame(), "Podaj ilosc dni do konca terminu przydatnosci");
                }
                else {
                    Calendar today = new GregorianCalendar();
                    String selectedProducts = new String();
                    selectedProducts += "Typ         | Data zakupu    | Data przydatnosci | Stan produktu  | Dni do konca przydatnosci\n";
                    boolean empty = true;
                    for(Product product : listOfProducts) {
                        int daysToExp = (int)((product.getExpDate().getTime().getTime() - today.getTime().getTime()) / (1000 * 60 * 60 * 24));
                        if(daysToExp >= 0 && product.getExpDate().get(Calendar.DAY_OF_MONTH) != today.get(Calendar.DAY_OF_MONTH)) {
                            daysToExp++;
                        }
                        if(daysToExp >= 0 && daysToExp <= Integer.parseInt(productDaysToExp.getText())) {
                            selectedProducts += product + " | " + daysToExp + "\n";
                            empty = false;
                        }
                    }
                    if(empty) {
                        JOptionPane.showMessageDialog(new JFrame(), "Brak produktow przydatnych tylko tyle dni");
                    }
                    else {
                        JOptionPane.showMessageDialog(new JFrame(), selectedProducts);
                    }
                }
            }
        });
        add(showExpButton);

        setVisible(true);
    }
}
