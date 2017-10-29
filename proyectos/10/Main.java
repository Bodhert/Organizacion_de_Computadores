import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class Main 
{
    public static void main(String[] args) throws Exception 
    {
        String fileName = "Main.jack"; // cambiar despues por lectura de argumentos (leer archivo )
        File file = new File(fileName);
        FileInputStream Opener = null;
        Opener = new FileInputStream(file);
        // create a CharStream that reads from standard input
        ANTLRInputStream input = new ANTLRInputStream(Opener);
        // create a lexer that feeds off of input CharStream
        JackLexer lexer = new JackLexer(input);
        // create a buffer of tokens pulled from the lexer
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        // create a parser that feeds off the tokens buffer
        JackParser parser = new JackParser(tokens);
        ParseTree tree = parser.class_1(); // begin parsing at init rule
        System.out.println(tree.toStringTree(parser)); // print LISP-style tree
        Opener.close();
    }
}