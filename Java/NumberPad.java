package app;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * A numeric keypad
 */
public class NumberPad extends    JPanel
{
	JButton btn0, btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btnC, btnDel;
	private ActionListener listener;
    /**
	 * 
	 */
	private static final long serialVersionUID = -3449140087047016040L;
	
	/**
     * Default Constructor
     */
    public NumberPad(ActionListener listener)
    {
    	super();
    	this.listener = listener;
        setupLayout();
    }

    /**
     * Setup and layout this NumberPad
     */
    private void setupLayout()
    {
    	 //Setting the layout
         this.setLayout(new GridLayout(4,3));
        
         //Adding the Buttons into the layout
         for(int i = 1; i <= 9; i++) addButton(new JButton(i + ""));
         addButton(new JButton("Del"));
         addButton(new JButton("0"));
         addButton(new JButton("C"));
         
         
         
    }
    private void addButton(JButton button) {
    	button.addActionListener(listener);
    	this.add(button);
    	
    }
}
