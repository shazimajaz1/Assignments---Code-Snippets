package app;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JLabel;
import javax.swing.border.EtchedBorder;

public class Display extends JLabel implements ActionListener {
	/**
	 * 
	 */
	private static final long serialVersionUID = 4087260026416787560L;

	public Display() {
		super(" ");
		this.setBorder(new EtchedBorder());
		this.setText("Enter Your PIN");
		if(this.getText().equals("Enter Your PIN")) this.setForeground(Color.gray);
		this.setHorizontalAlignment(RIGHT);

	}
	

	//this methods adds the defaults actions that will be performed when those buttons are pressed
	@Override
	public void actionPerformed(ActionEvent event) {
		
		//Actions associated
		String command;
		command = event.getActionCommand();
		//Actions associated with he Button
		if(command.equals("C")) {
			
			this.setText("Enter Your PIN");
			if(this.getText().equals("Enter Your PIN")) this.setForeground(Color.gray);
		}
		else if(command.equals("Del")) {
			if(this.getText().equals(" ")) this.setText(" ");
			else
				if(this.getText().length() == 1) this.setText(" ");
				else this.setText(this.getText().substring(0, this.getText().length()-1));
			
		}
		else {
			if(this.getText().equals("Enter Your PIN")) this.setText("*");
			
			else this.setText(this.getText() + "*");
			
			this.setForeground(Color.RED); //color red when anything other than the default
			
		}
	}
}
