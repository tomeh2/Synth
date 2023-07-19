#include "Parser.h"

#include "Logger.h"

Token* currToken;
int currTokenIndex;
int currOperatorIndex;

int Parser::accept(std::vector<Token*>* tokens, Token::TokenType expectedType)
{
    if (currToken->getType() == expectedType)
    {
        currTokenIndex++;
        if (currTokenIndex < tokens->size())
        {
            currToken = tokens->at(currTokenIndex);
        }
        return 1;
    }
    return 0;
}

int Parser::accept(std::vector<Token*>* tokens, Token::TokenType expectedType, std::string value)
{
    int retVal = 0;
    retVal = ((currToken->getType() == expectedType) && (value.compare(currToken->getData()) == 0)) ? 1 : 0;
    

    if (retVal == 1 && currTokenIndex < tokens->size())
    {
        currTokenIndex++;
        currToken = tokens->at(currTokenIndex);
    }

    return retVal;
}

int Parser::expect(Token::TokenType expectedType, Token* token)
{
    return 0;
}

int Parser::blockPatch(std::vector<Token*>* tokens, std::map<std::string, Patch*>* patches)
{
    Patch* p = new Patch;

    if (!accept(tokens, Token::STRING, "Patch"))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected Patch block");
        return -1;
    }

    if (!accept(tokens, Token::CURLY_START))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected {");
        return -1;
    }

    std::string lval;
    std::string rval;
    while (statement(tokens, &lval, &rval) == 0)
    {
        char msg[128];
        sprintf(msg, "Loaded patch parameter %s = %s", lval.c_str(), rval.c_str());
        Logger::log(Logger::INFO, msg);
        p->addPatchParameter(lval, rval);

        lval = "";
        rval = "";
    }

    while (blockOperator(tokens, p) == 0)
    {
        Logger::log(Logger::INFO, "Created new operator data object");
    }

    if (p->getPatchParameter("name") != "")
        patches->insert(std::pair<std::string, Patch*>(p->getPatchParameter("name"), p));
    else
        Logger::log(Logger::ERROR, "Ignoring a loaded patch object without a name");

    if (!accept(tokens, Token::CURLY_END))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected }");
        return -1;
    }

    return 0;
}

int Parser::blockOperator(std::vector<Token*>* tokens, Patch* patch)
{
    if (!accept(tokens, Token::STRING, "Operator"))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected Operator block");
        return -1;
    }

    if (!accept(tokens, Token::CURLY_START))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected {");
        return -1;
    }

    patch->addOperator();

    std::string lval;
    std::string rval;
    while (statement(tokens, &lval, &rval) == 0)
    {
        char msg[128];
        sprintf(msg, "Loaded operator parameter %s = %s", lval.c_str(), rval.c_str());
        Logger::log(Logger::INFO, msg);
        patch->addOperatorParameter(currOperatorIndex, lval, rval);

        lval = "";
        rval = "";
    }

    if (!accept(tokens, Token::CURLY_END))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected }");
        return -1;
    }

    currOperatorIndex++;
    return 0;
}

int Parser::statement(std::vector<Token*>* tokens, std::string* lvalue, std::string* rvalue)
{
    lvalue->append(currToken->getData());
    if (!accept(tokens, Token::STRING))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Statement lvalue must be of a string type");
        return -1;
    }

    if (!accept(tokens, Token::EQUALS))
    {
        currTokenIndex -= 1;
        currToken = tokens->at(currTokenIndex);
        Logger::log(Logger::ERROR, "Patch file parser error! Expected =");
        return -1;
    }

    rvalue->append(currToken->getData());
    if (!accept(tokens, Token::STRING) && !accept(tokens, Token::NUMBER_FLOAT) && !accept(tokens, Token::NUMBER_INT))
    {
        currTokenIndex -= 2;
        currToken = tokens->at(currTokenIndex);
        Logger::log(Logger::ERROR, "Patch file parser error! Expected a string statement");
        return -1;
    }

    if (!accept(tokens, Token::SEMICOLON))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected ;");
        return -1;
    }

    return 0;
}

int Parser::parse(std::vector<Token*>* tokens, std::map<std::string, Patch*>* patches)
{
    currTokenIndex = 0;
    currToken = tokens->at(currTokenIndex);
    
    while (currTokenIndex < tokens->size())
    {
        currOperatorIndex = 0;
        int errCode = blockPatch(tokens, patches);

        if (errCode != 0)
            return errCode;
    }

    Logger::log(Logger::INFO, "Patch file loaded successfully");
    return 0;
}
