/*
 * LoopStatementParser.cpp
 *
 *  Created on: Feb 16, 2020
 *      Author: dereknguyen
 */
#include <string>
#include "LoopStatementParser.h"
#include "StatementParser.h"
#include "ExpressionParser.h"
#include "../PascalParserTD.h"
#include "../PascalToken.h"
#include "../PascalError.h"
#include "../../Token.h"
#include "../../../intermediate/ICodeNode.h"
#include "../../../intermediate/ICodeFactory.h"
#include "../../../intermediate/icodeimpl/ICodeNodeImpl.h"

namespace wci { namespace frontend { namespace pascal { namespace parsers {

using namespace std;
using namespace wci::frontend::pascal;
using namespace wci::intermediate;
using namespace wci::intermediate::icodeimpl;
ICodeNode *LoopStatementParser::parse_statement(Token *token)
    throw (string)
{
    // Create the LOOP node.
    ICodeNode *loop_node =
            ICodeFactory::create_icode_node((ICodeNodeType) NT_LOOP);
    EnumSet<PascalTokenType> terminator_set(STMT_START_SET);
    terminator_set.insert(PT_WHEN);
    terminator_set.insert(PT_AGAIN);

    token = next_token(token);  // consume the LOOP

    StatementParser statement_parser(this);
    ExpressionParser expression_parser(this);

    // Parse the statement list terminated by the AGAIN or another WHEN token.
    // The LOOP node is the parent of the statement subtrees.
    while(token->get_type() != (TokenType) PT_AGAIN)
    {
        ICodeNode *another_when_test_node =
                ICodeFactory::create_icode_node((ICodeNodeType) NT_TEST);
    	//keep parsing the list until you arrive at AGAIN or WHEN
        statement_parser.parse_loop_again_list(token, loop_node, PT_WHEN, PT_AGAIN, MISSING_AGAIN);
        if(token->get_type() == (TokenType) PT_WHEN)
        {
        	//if token is WHEN, then you need to parse the expression
        	token = next_token(token);//consume WHEN
            // Parse the expression.
            // The TEST node adopts the expression subtree as its only child.
            // The LOOP node adopts the TEST node.
            ExpressionParser expression_parser(this);
            another_when_test_node->add_child(expression_parser.parse_statement(token));
            loop_node->add_child(another_when_test_node);

            //at this point, the token should be ==>
            if(token->get_type() != (TokenType) PT_EXIT_ARROW)
            {
            	//this is an error because we're missing the exit arrow
            	error_handler.flag(token, MISSING_EXIT_ARROW, this);
            }
            else
            {
            	//everything is fine, so just consume the ==>
                token = next_token(token);
            }
            //at this point, the token should be semicolon
            if(token->get_type() != (TokenType) PT_SEMICOLON)
            {
            	//this is an error because we're missing the semicolon
            	error_handler.flag(token, MISSING_SEMICOLON, this);
            }
            else
            {
            	//everything is fine, so just consume the ;
                token = next_token(token);
            }
            token = synchronize(terminator_set);//i added this
        }
    }

    token = next_token(token);//consume AGAIN

    return loop_node;
}

}}}}  // namespace wci::frontend::pascal::parsers




