/**
 * <h1>StatementParser</h1>
 *
 * <p>Parse a Pascal statement.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef STATEMENTPARSER_H_
#define STATEMENTPARSER_H_

#include <string>
#include "../PascalParserTD.h"
#include "../PascalToken.h"
#include "../../../intermediate/ICodeNode.h"

namespace wci { namespace frontend { namespace pascal { namespace parsers {

using namespace std;
using namespace wci::frontend::pascal;
using namespace wci::intermediate;

class StatementParser : public PascalParserTD
{
public:
    /**
     * Constructor.
     * @param parent the parent parser.
     */
    StatementParser(PascalParserTD *parent) : PascalParserTD(parent) {}

    /**
     * Parse a statement.
     * @param token the initial token.
     * @return the root node of the generated parse tree.
     * @throw a string message if an error occurred.
     */
    virtual ICodeNode *parse_statement(Token *token) throw (string);

    /**
     * Parse a statement list.
     * @param token the current token.
     * @param parent_node the parent node of the statement list.
     * @param terminator the token type of the node that terminates the list.
     * @param error_code the error code if the terminator token is missing.
     * @throw a string message if an error occurred.
     */
    void parse_list(Token *token, ICodeNode *parent_node,
                    const PascalTokenType terminator,
                    const PascalErrorCode error_code)
        throw (string);

    /**
     * Parse a statement list that has two terminators.
     * @param token the current token.
     * @param parent_node the parent node of the statement list.
     * @param terminator1 the first token type of the node that terminates the list.
     * @param terminator2 the second token type of the node that terminates the list.
     * @param error_code the error code if the terminator token is missing.
     * @throw a string message if an error occurred.
     */
    void parse_loop_again_list(Token *token, ICodeNode *parent_node,
                    		   const PascalTokenType terminator1,
							   const PascalTokenType terminator2,
							   const PascalErrorCode error_code)
        throw (string);

    // Synchronization set for starting a statement.
    static EnumSet<PascalTokenType> STMT_START_SET;

    // Synchronization set for following a statement.
    static EnumSet<PascalTokenType> STMT_FOLLOW_SET;
};

}}}}  // namespace wci::frontend::pascal::parsers

#endif /* STATEMENTPARSER_H_ */
