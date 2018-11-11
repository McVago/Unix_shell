#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <QMainWindow>

namespace Ui {
class File_Explorer;
}

class File_Explorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit File_Explorer(QWidget *parent = nullptr);
    ~File_Explorer();

private:
    Ui::File_Explorer *ui;
};

#endif // FILE_EXPLORER_H
