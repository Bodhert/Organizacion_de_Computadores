import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;
import java.io.StringWriter;
import java.io.StringReader;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Properties;
import java.util.Stack;

//main

public class Jack2XML
{
    public static class XMLEmitterVisitor  extends JackBaseVisitor<Void> 
    {
        Stack<String> nested_stack = new Stack();
        StringBuilder end_buf = new StringBuilder();

        public Void print_to_end_buf()
        {
            Stack<String> temp = new Stack();
            System.out.println(nested_stack);
            while(!nested_stack.empty()) temp.push(nested_stack.pop());
            while(!temp.empty()) end_buf.append(temp.pop() + "\n");  
            return null;
        }
        


         public Void visitClass_1(JackParser.Class_1Context ctx)
        {
              StringBuilder buf = new StringBuilder();
              System.out.println(" visitando a: visitClass_1 ");

              String open_class = "<" + ctx.getChild(0)+ ">";
              nested_stack.push(open_class);
              String keyword = "<keyword> " + ctx.getChild(0) + " </keyword>";
              nested_stack.push(keyword);
              //llamos a los hijos
        
                visitChildren(ctx);
        
              String closing_class = "</"+ ctx.getChild(0) +">";
              nested_stack.push(closing_class);
              buf.append("</symbol "+ ctx.getChild(2) +" symbol>\n");              
              return null;
              //return visitChildren(ctx); 
        }

        public Void visitClassName(JackParser.ClassNameContext ctx) 
        { 
            System.out.println(" visitando a: visitClassName ");
            String identifier = "<identifier> " + ctx.getText() + " </identifier>";
            nested_stack.push(identifier);
            return null; 
            //return visitChildren(ctx); 
        }

        public Void visitClassVarDec(JackParser.ClassVarDecContext ctx)
        { 
            System.out.println(" visitando a: visitClassVarDec ");
            return null;
        //     return visitChildren(ctx); 
        }

        public Void visitType(JackParser.TypeContext ctx) 
        {
            System.out.println("visitando a: " + "visitType" ); 
             return visitChildren(ctx); 
        }

        public Void visitSubroutineDec(JackParser.SubroutineDecContext ctx) 
        {
            String Open_SubroutineDec = "<subroutineDec> ";
            nested_stack.push(Open_SubroutineDec);
            //llamos a sus hijos
            System.out.println("visitando a: " + "visitSubroutineDec" ); 
            visitChildren(ctx);
            nested_stack.push(ctx.getChild(0).getText());
            String Close_SubroutineDec = "</subroutineDec> ";
            nested_stack.push(Close_SubroutineDec);
            return null;
             //return visitChildren(ctx); 
        }

        public Void visitParameterList(JackParser.ParameterListContext ctx) 
        {
            System.out.println("visitando a: " + "visitParameterList" ); 
             return visitChildren(ctx); 
        }

        public Void visitSubroutineBody(JackParser.SubroutineBodyContext ctx) 
        {
            System.out.println("visitando a: " + "visitSubroutineBody" ); 
             return visitChildren(ctx); 
        }

        public Void visitVarDec(JackParser.VarDecContext ctx) 
        {
            System.out.println("visitando a: " + "visitVarDec" ); 
             return visitChildren(ctx); 
        }

        public Void visitSubroutineName(JackParser.SubroutineNameContext ctx) 
        {
            System.out.println("visitando a: " + "visitSubroutineName" ); 
             return visitChildren(ctx); 
        }

        public Void visitVarName(JackParser.VarNameContext ctx) 
        {
            System.out.println("visitando a: " + "visitVarName" ); 
             return visitChildren(ctx); 
        }

        public Void visitStatements(JackParser.StatementsContext ctx) 
        {
            System.out.println("visitando a: " + "visitStatements" ); 
             return visitChildren(ctx); 
        }

        public Void visitStatement(JackParser.StatementContext ctx) 
        {
            System.out.println("visitando a: " + "visitStatement" ); 
             return visitChildren(ctx); 
        }

        public Void visitLetStatement(JackParser.LetStatementContext ctx) 
        {
            System.out.println("visitando a: " + "visitLetStatement" ); 
             return visitChildren(ctx); 
        }

        public Void visitIfStatement(JackParser.IfStatementContext ctx) 
        {
            System.out.println("visitando a: " + "visitIfStatement" ); 
             return visitChildren(ctx); 
        }

        public Void visitWhileStatement(JackParser.WhileStatementContext ctx) 
        {
            System.out.println("visitando a: " + "visitWhileStatement" ); 
             return visitChildren(ctx); 
        }

        public Void visitDoStatement(JackParser.DoStatementContext ctx) 
        {
            System.out.println("visitando a: " + "visitDoStatement" ); 
             return visitChildren(ctx); 
        }

        public Void visitReturnStatement(JackParser.ReturnStatementContext ctx) 
        {
            System.out.println("visitando a: " + "visitReturnStatement" ); 
             return visitChildren(ctx); 
        }

        public Void visitExpression(JackParser.ExpressionContext ctx) 
        {
            System.out.println("visitando a: " + "visitExpression" ); 
             return visitChildren(ctx); 
        }

        public Void visitTerm(JackParser.TermContext ctx) 
        {
            System.out.println("visitando a: " + "visitTerm" ); 
             return visitChildren(ctx); 
        }

        public Void visitSubroutineCall(JackParser.SubroutineCallContext ctx) 
        {
            System.out.println("visitando a: " + "visitSubroutineCall" ); 
             return visitChildren(ctx); 
        }

        public Void visitExpressionList(JackParser.ExpressionListContext ctx) 
        {
            System.out.println("visitando a: " + "visitExpressionList" ); 
             return visitChildren(ctx); 
        }

        public Void visitOp(JackParser.OpContext ctx) 
        {
            System.out.println("visitando a: " + "visitOp" ); 
             return visitChildren(ctx); 
        }

        public Void visitUnaryOp(JackParser.UnaryOpContext ctx) 
        {
            System.out.println("visitando a: " + "visitUnaryOp" ); 
             return visitChildren(ctx); 
        }

        public Void visitKeywordConstant(JackParser.KeywordConstantContext ctx) 
        {
            System.out.println("visitando a: " + "visitKeywordConstant" ); 
             return visitChildren(ctx); 
        }

    
        
        
        
    }

    public static void main(String[] args) throws Exception 
    {
        String fileName = "Main.jack"; // cambiar despues por lectura de argumentos (leer archivo )
        File file = new File(fileName);
        FileInputStream Opener = null;
        Opener = new FileInputStream(file);
        ANTLRInputStream input = new ANTLRInputStream(Opener);
        JackLexer lexer = new JackLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        JackParser parser = new JackParser(tokens);
        ParseTree tree = parser.class_1(); //regla inicial

        XMLEmitterVisitor visitor = new XMLEmitterVisitor();
        visitor.visit(tree);

        PrintWriter writer = new PrintWriter("salida.xml", "UTF-8");
        visitor.print_to_end_buf();
        writer.println(visitor.end_buf.toString());
        writer.close();
        Opener.close();
    }
}