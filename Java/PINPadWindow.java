package app;
import java.awt.*;
import javax.swing.*;

/**
 * A window containing a PIN entry pad.
 */
public class PINPadWindow extends JFrame
{
    /**
	 * 
	 */
	private static final long serialVersionUID = -6834960118098214136L;

	/**
     * Default Constructor.
     */
    public PINPadWindow()
    {
        super();
        setupLayout();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setResizable(false);
    }

    /**
     * Setup and layout this PINPadWindow
     */
    private void setupLayout()
    {
        Container     contentPane;
        
        setSize(300, 300); 

        contentPane = getContentPane();

        // Layout this PINPadWindow
       BorderLayout layout = new BorderLayout();
       contentPane.setLayout(layout);
       Display display = new Display();
       contentPane.add(display, BorderLayout.NORTH);
       if(display.getText().equals("") || display.getText().equals(null)) display.setText("Enter Your Pin");
       NumberPad pad = new NumberPad(display);
       contentPane.add(pad, BorderLayout.CENTER);
        
        
        
        
    }
}
