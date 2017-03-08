#include "projectexplorerwidget.h"
#include <QApplication>
#include <QSqlDatabase>
#include "db/QDjango.h"

#include "db/models/architectelement.h"
#include "db/models/docelement.h"
#include "db/models/imageselement.h"
#include "db/models/requirementelement.h"
#include "db/models/architectlinks.h"
#include "db/models/architecttypealias.h"

#include "db/models/glossaryelement.h"
#include "db/models/termselement.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProjectExplorerWidget w;
    w.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pdata");
    db.open();

    QDjango::setDatabase(db);

    QDjango::registerModel<DocElement>();
    QDjango::registerModel<ImagesElement>();
    QDjango::registerModel<RequirementElement>();
    QDjango::registerModel<ArchitectElement>();
    QDjango::registerModel<ArchitectLinks>();
    QDjango::registerModel<GlossaryElement>();
    QDjango::registerModel<TermsElement>();
    QDjango::registerModel<ArchitectTypeAlias>();

    QDjango::createTables();

    return a.exec();
}
