import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class Product {
    private String name;
    private Calendar buyDate;
    private Calendar expDate; // expiration date
    private boolean open; // state of product - opened if true, closed if false
    private SimpleDateFormat sdf = new SimpleDateFormat("yyyy MMM dd");

    public Product() {
    }

    public Product(String name, Calendar buyDate, Calendar expDate, boolean open) {
        this.name = name;
        this.buyDate = new GregorianCalendar(buyDate.get(Calendar.YEAR), buyDate.get(Calendar.MONTH), buyDate.get(Calendar.DAY_OF_MONTH));
        this.expDate = new GregorianCalendar(expDate.get(Calendar.YEAR), expDate.get(Calendar.MONTH), expDate.get(Calendar.DAY_OF_MONTH));
        this.open = open;
    }

   public String getName() {
        return this.name;
    }

    public Calendar getBuyDate() {
        return this.buyDate;
    }

    public Calendar getExpDate() {
        return  this.expDate;
    }

    public boolean getState() {
        return this.open;
    }

    @Override
    public String toString() {
        String opened = "zamkniete";
        if(this.open) {
            opened = "otwarte";
        }
        return this.name + " | " + sdf.format(this.buyDate.getTime()) + " | " + sdf.format(this.expDate.getTime()) + " | " + opened;
    }
}
