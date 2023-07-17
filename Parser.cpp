#include "Parser.h"

#include "Logger.h"

Token* currToken;
int currTokenIndex;
int currOperatorIndex;

int Parser::accept(std::vector<Token*>* tokens, Token::TokenType expectedType)
{
    if (currToken->getType() == expectedType)
    {
        if (currTokenIndex < tokens->size())
        {
            currTokenIndex++;
            currToken = tokens->at(currTokenIndex);
        }
        return 1;
    }
    return 0;
}

int Parser::accept(std::vector<Token*>* tokens, Token::TokenType expectedType, void* value)
{
    int retVal = 0;
    if (currToken->getType() == expectedType)
    {
        if (currToken->getType() == Token::STRING)
            retVal = strcmp(currToken->getStrData(), (char*) value) == 0 ? 1 : 0;
        else if (currToken->getType() == Token::NUMBER_INT)
            retVal = currToken->getIntData() == *((int*)value) ? 1 : 0;
        else if (currToken->getType() == Token::NUMBER_FLOAT)
            retVal = currToken->getFloatData() == *((float*)value) ? 1 : 0;
    }
    currTokenIndex++;

    if (currTokenIndex < tokens->size())
        currToken = tokens->at(currTokenIndex);

    return retVal;
}

int Parser::expect(Token::TokenType expectedType, Token* token)
{
    return 0;
}

int Parser::blockPatch(std::vector<Token*>* tokens, std::map<std::string, Patch*>* patches)
{
    Patch* p = new Patch;

    if (!accept(tokens, Token::STRING, (void*)("Patch")))
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
    std::string* rval = new std::string();
    while (statementString(tokens, &lval, rval) == 0)
    {
        char msg[128];
        sprintf(msg, "Loaded patch parameter %s = %s", lval.c_str(), rval->c_str());
        Logger::log(Logger::INFO, msg);
        p->addPatchParameter(lval, rval);

        lval = "";
        rval = new std::string;
    }

    while (blockOperator(tokens, p) == 0)
    {
        Logger::log(Logger::INFO, "Created new operator data object");
    }

    patches->insert(std::pair<std::string, Patch*>("123", p));

    if (!accept(tokens, Token::CURLY_END))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected }");
        return -1;
    }

    return 0;
}

int Parser::blockOperator(std::vector<Token*>* tokens, Patch* patch)
{
    if (!accept(tokens, Token::STRING, (void*)("Operator")))
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
    float* rval = new float;
    while (statementFloat(tokens, &lval, rval) == 0)
    {
        char msg[128];
        sprintf(msg, "Loaded operator parameter %s = %f", lval.c_str(), *rval);
        Logger::log(Logger::INFO, msg);
        patch->addOperatorParameter(currOperatorIndex, lval, rval);

        lval = "";
        rval = new float;
    }

    if (!accept(tokens, Token::CURLY_END))
    {
        Logger::log(Logger::ERROR, "Patch file parser error! Expected }");
        return -1;
    }

    currOperatorIndex++;
    return 0;
}

int Parser::statementString(std::vector<Token*>* tokens, std::string* lvalue, std::string* rvalue)
{
    lvalue->append(currToken->getStrData());
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

    rvalue->append(currToken->getStrData());
    if (!accept(tokens, Token::STRING))
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

int Parser::statementFloat(std::vector<Token*>* tokens, std::string* lvalue, float* rvalue)
{
    lvalue->append(currToken->getStrData());
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

    *rvalue = currToken->getFloatData();
    if (!accept(tokens, Token::NUMBER_FLOAT))
    {
        currTokenIndex -= 2;
        currToken = tokens->at(currTokenIndex);
        Logger::log(Logger::ERROR, "Patch file parser error! Expected a float value");
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
    currOperatorIndex = 0;

    while (currTokenIndex < tokens->size())
    {
        int errCode = blockPatch(tokens, patches);

        if (errCode != 0)
            return errCode;
    }

    Logger::log(Logger::INFO, "Patch file loaded successfully");
    return 0;
}
