/*
 * LoopStatementParser.h
 *
 *  Created on: Feb 16, 2020
 *      Author: dereknguyen
 */

#ifndef WCI_FRONTEND_PASCAL_PARSERS_LOOPSTATEMENTPARSER_H_
#define WCI_FRONTEND_PASCAL_PARSERS_LOOPSTATEMENTPARSER_H_

#include <string>
#include "StatementParser.h"
#include "../../Token.h"

namespace wci { namespace frontend { namespace pascal { namespace parsers {

using namespace std;
using namespace wci::frontend;
using namespace wci::frontend::pascal;
using namespace wci::intermediate;

class LoopStatementParser : public StatementParser
{
public:
    /**
     * Constructor.
     * @param parent the parent parser.
     */
    LoopStatementParser(PascalParserTD *parent) : StatementParser(parent) {}

    /**
     * Parse a LOOP statement.
     * @param token the initial token.
     * @return the root node of the generated parse tree.
     * @throw a string message if an error occurred.
     */
    ICodeNode *parse_statement(Token *token) throw (string);
};

}}}}  // namespace wci::frontend::pascal::parsers

#endif /* WCI_FRONTEND_PASCAL_PARSERS_LOOPSTATEMENTPARSER_H_ */


