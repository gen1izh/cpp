#include "highlighter.h"


Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {

  QFont   fnt;

  fnt.fromString(QString( "Arial,14,-1,5,50,0,0,0,0,0" ));

  HighlightingRule rule;


  QStringList keywordPatterns;
  keywordPatterns << "[H1]" << "[H2]" << "[H3]" << "[H4]"
                  << "[P1]" << "[P2]" << "[P3]" << "[P4]"
                  << "[UL]" << "[LI]" << "[U]" << "[I]" << "[B]"
                  << "[IMG]" << "    [FILENAME]" << "[NAME]"
                  << "[BODY_INFO]" << "[BODY_BR]" << "[BODY_CR]" << "[BODY_NFR]"<< "[BODY_FR]"
                  << "[GLOSSARY]"  << "[TERMINS]" << "[TERM]" << "[GOTO_ANCHR]" << "[ANCHOR]";

  keywordPatterns << "[/H1]" << "[/H2]" << "[/H3]" << "[/H4]"
                  << "[/P1]" << "[/P2]" << "[/P3]" << "[/P4]"
                  << "[/UL]" << "[/LI]" << "[/U]" << "[/I]" << "[/B]"
                  << "[/IMG]" << "    [/FILENAME]" << "[/NAME]"
                  << "[/BODY_INFO]" << "[/BODY_BR]" << "[/BODY_CR]" << "[/BODY_NFR]"<< "[/BODY_FR]"
                  << "[/GLOSSARY]"  << "[/TERMINS]" << "[/TERM]" << "[/GOTO_ANCHR]" << "[/ANCHOR]";

  _allTextFormat.setFont(fnt);
   rule.format  = _allTextFormat;
   rule.pattern = QRegExp( "." );
  _highlightingRules.append( rule );

  _numbericFormat.setFont( fnt );
  _numbericFormat.setForeground( Qt::red );
  _numbericFormat.setFontWeight( QFont::Bold );
   rule.format  = _numbericFormat;
   rule.pattern = QRegExp( "[0-9]" );
  _highlightingRules.append( rule );

  _keywordFormat.setFont( fnt );
  _keywordFormat.setForeground( Qt::darkBlue );
  _keywordFormat.setFontWeight( QFont::Bold );
  foreach (const QString &pattern, keywordPatterns) {
    rule.format  = _keywordFormat;
    rule.pattern = QRegExp( pattern );
   _highlightingRules.append( rule );
  }

  _classFormat.setFont( fnt );
  _classFormat.setFontWeight( QFont::Bold );
  _classFormat.setForeground( Qt::darkMagenta );
   rule.pattern = QRegExp( "\\bQ[A-Za-z]+\\b" );
   rule.format  = _classFormat;
  _highlightingRules.append( rule );

  _singleLineCommentFormat.setFont( fnt );
  _singleLineCommentFormat.setForeground( Qt::darkGreen );
   rule.pattern = QRegExp( "//[^\n]*" );
   rule.format  = _singleLineCommentFormat;
  _highlightingRules.append(rule);

  _multiLineCommentFormat.setFont( fnt );
  _multiLineCommentFormat.setForeground( Qt::red );
  _quotationFormat.setForeground( Qt::darkGreen );
  _quotationFormat.setFont( fnt );
   rule.pattern = QRegExp( "\".*\"" );
   rule.format  = _quotationFormat;
  _highlightingRules.append( rule );

  _functionFormat.setFont( fnt );
  _functionFormat.setFontItalic(true);
  _functionFormat.setForeground(Qt::blue);
   rule.pattern = QRegExp( "\\b[A-Za-z0-9_]+(?=\\()" );
   rule.format  = _functionFormat;
  _highlightingRules.append(rule);
  _commentStartExpression = QRegExp("/\\*");
  _commentEndExpression = QRegExp("\\*/");

}

/*
 * Highlights the given text block
 */
void Highlighter::highlightBlock( const QString &text ) {
  foreach ( const HighlightingRule &rule, _highlightingRules ) {
    QRegExp expression(rule.pattern);
    int index = expression.indexIn(text);
    while ( index >= 0 ) {
      int length = expression.matchedLength();
      setFormat( index, length, rule.format );
      index = expression.indexIn( text, index + length );
    }
  }

  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1)
      startIndex = _commentStartExpression.indexIn( text );

  while (startIndex >= 0) {
    int endIndex = _commentEndExpression.indexIn( text, startIndex );
    int commentLength;
    if (endIndex == -1) {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    } else {
      commentLength = endIndex - startIndex
                      + _commentEndExpression.matchedLength();
    }
    setFormat(startIndex, commentLength, _multiLineCommentFormat);
    startIndex = _commentStartExpression.indexIn( text, startIndex + commentLength );
  }
}
