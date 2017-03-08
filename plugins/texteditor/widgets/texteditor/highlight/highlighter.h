#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

/*!
 * \brief Класс подсветки кода в скрипте
 */
class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT

  public:
    Highlighter(QTextDocument *parent = 0);

  protected:
    /*!
     * \brief Highlights the given text block
     * \param text
     */
    void highlightBlock(const QString &text);

  private:

    /*!
     * \brief
     */
    struct HighlightingRule {
      QRegExp         pattern;
      QTextCharFormat format;
    };

    /*!
     * \brief _highlightingRules
     */
    QVector<HighlightingRule> _highlightingRules;

    /*!
     * \brief _commentStartExpression
     */
    QRegExp _commentStartExpression;

    /*!
     * \brief _commentEndExpression
     */
    QRegExp _commentEndExpression;

    /*!
     * \brief _allTextFormat
     */
    QTextCharFormat _allTextFormat;

    /*!
     * \brief _keywordFormat
     */
    QTextCharFormat _keywordFormat;

    /*!
     * \brief _numbericFormat
     */
    QTextCharFormat _numbericFormat;

    /*!
     * \brief _classFormat
     */
    QTextCharFormat _classFormat;

    /*!
     * \brief _singleLineCommentFormat
     */
    QTextCharFormat _singleLineCommentFormat;

    /*!
     * \brief _multiLineCommentFormat
     */
    QTextCharFormat _multiLineCommentFormat;

    /*!
     * \brief _quotationFormat
     */
    QTextCharFormat _quotationFormat;

    /*!
     * \brief _functionFormat
     */
    QTextCharFormat _functionFormat;
};

#endif // HIGHLIGHTER_H
