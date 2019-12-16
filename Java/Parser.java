
import java.io.IOException;
import java.util.Scanner;

public class Parser 
{
	static String inputString;
	static int index = 0;
	static int errorflag = 0;
	
	private char token()
	{ 
		return(inputString.charAt(index)); 
	}
	
	private void advancePtr()
	{ 
		if (index < (inputString.length()-1)) index++; 
	}
	
	private void match(char T)
	{
		if (T == token()) advancePtr(); else error(); 
	}
	
	private void error()
	{
		System.out.println("error at position: " + index);
		errorflag = 1;
		advancePtr();
	}
	

	private void javaclass()
	{
		classname();
		if(token() == 'X') // check for optional <extends classname>
		{
			match('X');
			classname();
		}
		match('B');
		varlist();
		match(';'); //varlist should be followed by ;
		while(token() == 'P' | token() == 'V') //1st of method can be p or v
		{
			method();
		}
		match('E');
	}
	
	
	// WRITE YOUR REST OF THE PARSER HERE
	//----------------------
	
	private void classname()
	{
		if(token() == 'C')
		{
			match('C');
		}
		else
		{
			match('D');
		}
	}
	
	private void varlist()
	{
		vardef();
		while(token() == ',')
		{
			match(',');
			vardef();
		}
	}
	
	private void vardef()
	{
		if(token() == 'I' || token() == 'S')
		{
			type();
			varname();
		}
		else
		{
			classname();
			varref();
		}
	}
	
	private void start()
	{
		javaclass();
		match('$');
		if (errorflag == 0)
		{
			System.out.println("legal." + "\n");
		}
		else
		{
			System.out.println("errors found." + "\n");
		}
	}
	
	private void type()
	{
		if(token() == 'I')
		{
			match('I');
		}
		else
		{
			match('S');
		}
	}
	
	private void varname()
	{
		letter();
		while(token()=='Y' || token()=='Z' || token()=='0' || token()=='1' || token()=='2' || token()=='3')
		{
			pchar(); //using pchar to avoid conflict with java char.
		}
	}
	
	private void letter()
	{
		if(token() == 'Y')
		{
			match('Y');
		}
		else
		{
			match('Z');
		}
	}
	
	private void pchar()
	{
		if(token()=='Y' || token()=='Z')
		{
			letter();
		}
		else
		{
			digit();
		}
	}
	
	public void digit()
	{
		switch ( token() )
		{
			case '0':
				match('0');
			break;
			case '1':
				match('1');
			break;
			case '2':
				match('2');
			break;
			default: 
				match('3');
			break;
		}
	}
	
	public void integer()
	{
		digit();
		while(token() == '0' || token() == '1' || token() == '2' || token() == '3')
		{
			digit();
		}
	}
	
	public void varref()
	{
		if (token()=='J')
		{
			match('J');
		}
		else
		{
			match('K');
		}
	}
	
	public void method()
	{
		accessor();
		type();
		methodname();
		match('(');
		if(token()=='I' || token()=='S' || token()=='C' || token()=='D')
		{
			varlist();
		}
		match(')');
		match('B');
		while(token()=='F' || token()=='Y' || token()=='Z' || token()=='W')
		{
			statemt();
		}
		returnstatemt();
		match('E');
	}
	
	public void accessor()
	{
		if(token()=='P')
		{
			match('P');
		}
		else
		{
			match('V');
		}
	}

	public void methodname() {
		if(token()=='M'){
			match('M');
		} else {
			match('N');
		}
	}

	public void statemt() {
		if(token()=='F') {
			ifstatemt();

		} else if(token() == 'Y' || token() == 'Z'){
			assignstatemt();
			match(';');
		} else {
			whilestatemt();
		}
	}

	public void ifstatemt() {
		match('F');
		cond();
		match('T');
		match('B');
		while(token()=='F' || token()=='Y' || token() == 'Z' || token() == 'W'){
			statemt();
		}
		match('E');
		if(token()=='L'){
			match('L');
			match('B');
			while(token()=='F' || token()=='Y' || token() == 'Z' || token() == 'W'){
				statemt();
			}
			match('E');
		}
	}

	public void mathexpr() {
		factor();
		while(token() == '+'){
			match('+');
			factor();
		}

	}

	public void assignstatemt() {
		if(token() == 'Y' || token() =='Z'){
			varname();
			match('=');
			mathexpr();
		} else {
			varref();
			match('=');
			getvarref();
		}
	}

	public void whilestatemt() {
		match('W');
		cond();
		match('T');
		match('B');

		while(token()=='F' || token()=='Y' || token() == 'Z' || token() == 'W'){
			statemt();
		}

		match('E');
	}

	public void cond(){
		match('(');
		oprnd();
		operator();
		oprnd();
		match(')');
	}
	public void factor(){
		oprnd();
		while(token() == '*'){
			match('*');
			oprnd();
		}
	}
	public void oprnd() {
		if(token() == '0' || token() == '1' || token() == '2' || token() == '3'){ //first of int
			integer();
		} else if(token() =='Y' || token() == 'Z'){ //check for first of varname
			varname();
		} else if(token() == '('){
			match('(');
			mathexpr();
			match(')');
		} else {
			methodcall();
		}
	}

	public void methodcall(){
		varref();
		match('.');
		methodname();
		match('(');
		if(token() == 'I' || token() == 'S' || token() == 'C' || token() == 'D'){ //first of var list
			varlist();
		}
		match(')');
	}

	public void getvarref() {
		if(token() == 'O'){
			match('O');
			classname();
			match('(');
			match(')');
		} else {
			methodcall();
		}
	}

	public void operator() {
		if(token() == '<'){
			match('<');
		} else if(token()=='='){
			match('=');
		} else if(token()=='>'){
			match('>');
		} else {
			match('!');
		}
	}

	public void returnstatemt() {
		match('R');
		varname();
		match(';');
	}


	
	public static void main (String[] args) throws IOException
	{
		Parser rec = new Parser();
		Scanner input = new Scanner(System.in);
		System.out.print("\n" + "enter an expression: ");
		inputString = input.nextLine();

		rec.start();
		
	}
	
}