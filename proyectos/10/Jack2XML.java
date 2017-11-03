import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.StringWriter;
import java.io.StringReader;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;

//mainf

public class Jack2XML
{

    public static class XMLEmitter  extends JackBaseListener
    {
        StringBuilder buf = new StringBuilder();
        StringBuilder buf_t = new StringBuilder();
        
        int globalTabs = 0; 
        // Generated from Jack.g4 by ANTLR 4.7

        public String generateTab(int tabs)
        {
            String tab = "";
            for(int i = 0; i < tabs; ++i) tab += "  ";
            return tab;
        }

        public void enterClass_1(JackParser.Class_1Context ctx) 
        {
            System.out.println("entro a enterClass_1 con: " + ctx.getText());
            buf.append("<" + "class" + ">\n");
            buf_t.append("<tokens>\n");
            globalTabs++;
            String tab = generateTab(globalTabs);
            // buf.append(tab + "<keyword> " + "class" + " </keyword>\n");
            // buf.append(tab + "<identifier> " + ctx.getChild(1).getText() + " </identifier>\n");
           // buf.append(tab + "<symbol> " + "{" + " </symbol>\n");
            
        }

        public void exitClass_1(JackParser.Class_1Context ctx) 
        {
            String tab = generateTab(globalTabs);
            System.out.println(tab + "entro a exitClass_1 con: " + ctx.getText());
           // buf.append(tab + "<symbol> " + "}" + " </symbol>\n");
            globalTabs--;
            tab = generateTab(globalTabs);
            buf.append(tab + "</" + "class" + ">\n");
            buf_t.append("</tokens>");
        }

        public void enterClassVarDec(JackParser.ClassVarDecContext ctx) 
        {
            System.out.println("entro a enterClassVarDec con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<classVarDec>\n");
            globalTabs++;
        }

        public void exitClassVarDec(JackParser.ClassVarDecContext ctx) 
        {
            System.out.println("entro a exitClassVarDec con: " + ctx.getText());
            globalTabs--;
            String tab = generateTab(globalTabs);
            buf.append(tab + "</classVarDec>\n");
        }

        // public void enterType(JackParser.TypeContext ctx) 
        // {
        //     System.out.println("entro a enterType con: " + ctx.getText());
        // }

        // public void exitType(JackParser.TypeContext ctx) 
        // {
        //     System.out.println("entro a exitType con: " + ctx.getText());
        // }

        public void enterSubroutineDec(JackParser.SubroutineDecContext ctx) 
        {
            String tab = generateTab(globalTabs);
            System.out.println("entro a enterSubroutineDec con: " + ctx.getText());
            buf.append(tab + "<subroutineDec>\n");
            globalTabs++;
            tab = generateTab(globalTabs);
            // buf.append(tab + "<keyword> " + ctx.getChild(0) + " </keyword>\n");
            // buf.append(tab + "<keyword> " + ctx.getChild(1) + " </keyword>\n");            
            //buf.append(tab + "<identifier> " + ctx.getChild(2).getText() + " </identifier>\n");                        
        }

        public void exitSubroutineDec(JackParser.SubroutineDecContext ctx) 
        {
            String tab;

            globalTabs--;
            tab = generateTab(globalTabs);
            buf.append(tab + "</subroutineDec>\n");
            System.out.println("entro a exitSubroutineDec con: " + ctx.getText());
        }

        public void enterParameterList(JackParser.ParameterListContext ctx) 
        {
            System.out.println("entro a enterParameterList con: " + ctx.getText());
            String tab = generateTab(globalTabs);
           // buf.append(tab + "<symbol> " + "(" + " </symbol>\n");           
            buf.append(tab + "<parameterList>\n");
            globalTabs++;
        }

        public void exitParameterList(JackParser.ParameterListContext ctx) 
        {
            System.out.println("entro a exitParameterList con: " + ctx.getText());
            globalTabs--;
            String tab = generateTab(globalTabs);
            buf.append(tab + "</parameterList>\n");

           // buf.append(tab + "<symbol> " + ")" + " </symbol>\n");            
            
        }

        public void enterSubroutineBody(JackParser.SubroutineBodyContext ctx) 
        {
            System.out.println("entro a enterSubroutineBody con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<subroutineBody>\n");
            globalTabs++;
            tab = generateTab(globalTabs);
            // buf.append(tab + "<symbol> " +  "{" + " </symbol>\n");
        }

        public void exitSubroutineBody(JackParser.SubroutineBodyContext ctx) 
        {
            System.out.println("entro a exitSubroutineBody con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            // buf.append(tab + "<symbol> " +  "}" + " </symbol>\n");            
            globalTabs--;
            tab = generateTab(globalTabs);
            buf.append(tab + "</subroutineBody>\n");
        }

        public void enterVarDec(JackParser.VarDecContext ctx) 
        {
            System.out.println("entro a enterVarDec con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<varDec>\n");
            globalTabs++;
            tab = generateTab(globalTabs);
            // buf.append(tab + "<keyword> " + "var" + " </keyword>\n" );
            //buf.append(tab + "<identifier> " + ctx.getChild(1).getText() + " </identifier>\n" );            
            
        }

        public void exitVarDec(JackParser.VarDecContext ctx) 
        {
            System.out.println("entro a exitVarDec con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            // buf.append(tab + "<symbol> " + ";" + " </symbol>\n");            
            globalTabs--;
            tab = generateTab(globalTabs);
            buf.append(tab + "</varDec>\n");
        }

        // public void enterClassName(JackParser.ClassNameContext ctx) 
        // {
        //     System.out.println("entro a enterClassName con: " + ctx.getText());
        // }

        // public void exitClassName(JackParser.ClassNameContext ctx) 
        // {
        //     System.out.println("entro a exitClassName con: " + ctx.getText());
        // }

        // public void enterSubroutineName(JackParser.SubroutineNameContext ctx) 
        // {
        //     System.out.println("entro a enterSubroutineName con: " + ctx.getText());
        // }

        public void exitSubroutineName(JackParser.SubroutineNameContext ctx) 
        {
            System.out.println("entro a exitSubroutineName con: " + ctx.getText());
        }

        // public void enterVarName(JackParser.VarNameContext ctx) 
        // {
        //     System.out.println("entro a enterVarName con: " + ctx.getText());
        // }

        public void exitVarName(JackParser.VarNameContext ctx) 
        {
            System.out.println("entro a exitVarName con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            //buf.append(tab + "<identifier> " + ctx.getText() + " </identifier>\n");
        }

        public void enterStatements(JackParser.StatementsContext ctx) 
        {
            System.out.println("entro a enterStatements con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<statements>\n");
            globalTabs++;
        }

        public void exitStatements(JackParser.StatementsContext ctx) 
        {
            System.out.println("entro a exitStatements con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            globalTabs--;
            tab = generateTab(globalTabs);
            buf.append(tab + "</statements>\n");
            
        }

        public void enterStatement(JackParser.StatementContext ctx) 
        {
            System.out.println("entro a enterStatement con: " + ctx.getText());
        }

        public void exitStatement(JackParser.StatementContext ctx) 
        {
            System.out.println("entro a exitStatement con: " + ctx.getText());
        }

        public void enterLetStatement(JackParser.LetStatementContext ctx) 
        {
            System.out.println("entro a enterLetStatement con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<letStatement>\n");
            globalTabs++;
        }

        public void exitLetStatement(JackParser.LetStatementContext ctx) 
        {
            globalTabs--;
            String tab = generateTab(globalTabs);
            buf.append(tab + "</letStatement>\n");            
            System.out.println("entro a exitLetStatement con: " + ctx.getText());
        }

        public void enterIfStatement(JackParser.IfStatementContext ctx) 
        {
            System.out.println("entro a enterIfStatement con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<ifStatement>\n");
            globalTabs++;
        }

        public void exitIfStatement(JackParser.IfStatementContext ctx) 
        {
            System.out.println("entro a exitIfStatement con: " + ctx.getText());
            globalTabs--;
            String tab = generateTab(globalTabs);            
            buf.append(tab + "</ifStatement>\n");            
        }

        public void enterWhileStatement(JackParser.WhileStatementContext ctx) 
        {
            System.out.println("entro a enterWhileStatement con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<whileStatement>\n");
            globalTabs++;
        }

        public void exitWhileStatement(JackParser.WhileStatementContext ctx) 
        {
            System.out.println("entro a exitWhileStatement con: " + ctx.getText());
            globalTabs--;
            String tab = generateTab(globalTabs);
            buf.append(tab + "</whileStatement>\n");   
        }

        public void enterDoStatement(JackParser.DoStatementContext ctx) 
        {
            System.out.println("entro a enterDoStatement con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<doStatement>\n");
            globalTabs++;
        }

        public void exitDoStatement(JackParser.DoStatementContext ctx) 
        {
            System.out.println("entro a exitDoStatement con: " + ctx.getText());
            globalTabs--;
            String tab = generateTab(globalTabs);
            buf.append(tab + "</doStatement>\n");   
        }

        public void enterReturnStatement(JackParser.ReturnStatementContext ctx) 
        {
            System.out.println("entro a enterReturnStatement con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<returnStatement>\n");
            globalTabs++;
        }

        public void exitReturnStatement(JackParser.ReturnStatementContext ctx) 
        {
            System.out.println("entro a exitReturnStatement con: " + ctx.getText());
            globalTabs--;
            String tab = generateTab(globalTabs);
            buf.append(tab + "</returnStatement>\n"); 
        }

        public void enterExpression(JackParser.ExpressionContext ctx) 
        {
            System.out.println("entro a enterExpression con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<expression>\n");
            globalTabs++;
        }

        public void exitExpression(JackParser.ExpressionContext ctx) 
        {
            System.out.println("entro a exitExpression con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            globalTabs--;
            tab = generateTab(globalTabs);
            buf.append(tab + "</expression>\n");
        }

        public void enterTerm(JackParser.TermContext ctx) 
        {
            System.out.println("entro a enterTerm con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<term>\n");
            globalTabs++;
        }

        public void exitTerm(JackParser.TermContext ctx) 
        {
            System.out.println("entro a exitTerm con: " + ctx.getText());
            globalTabs--;
            String tab = generateTab(globalTabs);
            buf.append(tab + "</term>\n");
        }

        public void enterSubroutineCall(JackParser.SubroutineCallContext ctx) 
        {
            System.out.println("entro a enterSubroutineCall con: " + ctx.getText());
        }

        public void exitSubroutineCall(JackParser.SubroutineCallContext ctx) 
        {
            System.out.println("entro a exitSubroutineCall con: " + ctx.getText());
        }

        public void enterExpressionList(JackParser.ExpressionListContext ctx) 
        {
            System.out.println("entro a enterExpressionList con: " + ctx.getText());
            String tab = generateTab(globalTabs);
            buf.append(tab + "<expressionList>\n");
            globalTabs++;
        }

        public void exitExpressionList(JackParser.ExpressionListContext ctx) 
        {
            System.out.println("entro a exitExpressionList con: " + ctx.getText());
            globalTabs--;
            String tab = generateTab(globalTabs);
            buf.append(tab + "</expressionList>\n" );
        }

        public void enterOp(JackParser.OpContext ctx) 
        {
            System.out.println("entro a enterOp con: " + ctx.getText());
        }

        public void exitOp(JackParser.OpContext ctx) 
        {
            System.out.println("entro a exitOp con: " + ctx.getText());
        }

        public void enterUnaryOp(JackParser.UnaryOpContext ctx) 
        {
            System.out.println("entro a enterUnaryOp con: " + ctx.getText());
        }

        public void exitUnaryOp(JackParser.UnaryOpContext ctx) 
        {
            System.out.println("entro a exitUnaryOp con: " + ctx.getText());
        }

        public void enterKeywordConstant(JackParser.KeywordConstantContext ctx) 
        {
            System.out.println("entro a enterKeywordConstant con: " + ctx.getText());
        }

        public void exitKeywordConstant(JackParser.KeywordConstantContext ctx) 
        {
            System.out.println("entro a exitKeywordConstant con: " + ctx.getText());
        }

        // public void enterEveryRule(ParserRuleContext ctx) 
        // {
        //     System.out.println("entro a enterEveryRule con: " + ctx.getText());
        // }

        // public void exitEveryRule(ParserRuleContext ctx) 
        // {
        //     System.out.println("entro a exitEveryRule con: " + ctx.getText());
        // }
        
        public boolean isInteger(String s) {  
            return s != null && s.matches("[-+]?\\d*");  
        }  

        public void visitTerminal(TerminalNode node) 
        {
            System.out.println("entro a visitTerminal con: " + node.getText());
            String tab = generateTab(globalTabs);
            String terminal = node.getText();
            Boolean isString =  terminal.startsWith("\"") && terminal.endsWith("\"");
            Boolean isInt = isInteger(terminal);
            if(
                   terminal.equals(",") 
                || terminal.equals("=") 
                || terminal.equals(".")
                || terminal.equals("{") 
                || terminal.equals("}") 
                || terminal.equals("(")
                || terminal.equals(")")
                || terminal.equals(";")
                || terminal.equals("<")
                || terminal.equals(">")
                || terminal.equals("[")
                || terminal.equals("]")
                || terminal.equals("/")
                || terminal.equals("+")
                || terminal.equals("-")
                || terminal.equals("|")    
                || terminal.equals("&")
                || terminal.equals("\"")
                || terminal.equals("*")
                || terminal.equals("~")                
              )
            {
                if(terminal.equals("<")) terminal = "&lt;";
                else if(terminal.equals(">")) terminal = "&gt;";
                else if(terminal.equals("&")) terminal = "&amp;";
                else if(terminal.equals("\"")) terminal = "&quot;";

                buf.append(tab + "<symbol> " + terminal + " </symbol>\n");
                buf_t.append("<symbol> " + terminal + " </symbol>\n");
            } 
            else if(!(
                           terminal.equals("class") 
                        || terminal.equals("constructor") 
                        || terminal.equals("function")
                        || terminal.equals("method") 
                        || terminal.equals("field") 
                        || terminal.equals("static") 
                        || terminal.equals("var") 
                        || terminal.equals("int") 
                        || terminal.equals("char") 
                        || terminal.equals("boolean") 
                        || terminal.equals("void") 
                        || terminal.equals("true")
                        || terminal.equals("false") 
                        || terminal.equals("null") 
                        || terminal.equals("this") 
                        || terminal.equals("let")
                        || terminal.equals("do") 
                        || terminal.equals("if") 
                        || terminal.equals("else")
                        || terminal.equals("while") 
                        || terminal.equals("return")
                        || terminal.equals(";")
                        || terminal.equals(",")
                        || isString
                        || isInt
                      )
                    )
            {
                buf.append(tab + "<identifier> " + terminal + " </identifier>\n");
                buf_t.append("<identifier> " + terminal + " </identifier>\n");
            }
            else if(isString)
            {
                int posFirstQuote = terminal.indexOf("\"") + 1;
                int posSecondQuote = terminal.lastIndexOf("\"");      
                terminal = terminal.substring(posFirstQuote,posSecondQuote);
                //System.out.println(terminal +  "asdfasdfsadfasdaa--------------------");
                buf.append(tab + "<stringConstant> " + terminal + " </stringConstant>\n");
                buf_t.append("<stringConstant> " + terminal + " </stringConstant>\n");
            }
            else if(isInt)
            {
                buf.append(tab + "<integerConstant> " + terminal + " </integerConstant>\n");
                buf_t.append("<integerConstant> " + terminal + " </integerConstant>\n");
            }
            else
            {
                buf.append(tab + "<keyword> " + terminal + " </keyword>\n");
                buf_t.append("<keyword> " + terminal + " </keyword>\n");
            }
        }

        public void visitErrorNode(ErrorNode node) 
        {
            System.out.println("entro a visitErrorNode con: " + node.getText());
        }


    }

    public static void main(String[] args) throws Exception 
    {
        String fileName;
        if(args != null)
        {
            fileName = args[0]; // cambiar despues por lectura de argumentos (leer archivo )
            String outFile = fileName.substring(0,fileName.lastIndexOf("."));
            File file = new File(fileName);
            FileInputStream Opener = null;
            Opener = new FileInputStream(file);
            ANTLRInputStream input = new ANTLRInputStream(Opener);
            JackLexer lexer = new JackLexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            JackParser parser = new JackParser(tokens);

            ParseTree tree = parser.class_1(); //regla inicial
            ParseTreeWalker walker = new ParseTreeWalker();
            XMLEmitter converter = new XMLEmitter();
            walker.walk(converter, tree);
    
            PrintWriter writer = new PrintWriter(outFile + "1.xml","UTF-8");
            writer.print(converter.buf.toString());
            writer.close();
            PrintWriter writer_T = new PrintWriter(outFile + "1T.xml","UTF-8");
            writer_T.println(converter.buf_t.toString());
            writer_T.close();
            Opener.close();
        }
        
    }
}