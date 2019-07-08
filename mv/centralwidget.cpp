#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent),
  list(new ListView(this)),
  adapter(new ListModelAdapter(this)),
  actionValue(new QDoubleSpinBox(this)),
  searchInput(new QLineEdit(this)),
  searchFilters(new QComboBox(this))
{
  // make buttons section
  QWidget* optWidget = new QWidget(this);
  QVBoxLayout* optLayout = new QVBoxLayout(optWidget);

  QPushButton* addBtn = new QPushButton("Insert", optWidget);
  QPushButton* simAttBtn = new QPushButton("Sim. attack", optWidget);
  simAttBtn->setToolTip("Click to make the selected Norvarad perform an attack");
  QPushButton* simDefBtn = new QPushButton("Sim. defense", optWidget);
  simDefBtn->setToolTip("Set a value and click to test the defense of the selected Norvarad");
  QPushButton* removeBtn = new QPushButton("Remove", optWidget);
  removeBtn->setToolTip("Removes the selected Norvarad");

  insType = new QComboBox(optWidget);
  QPixmap defIco(":/img/defense.png");
  defIco = defIco.scaled(40,40, Qt::KeepAspectRatio);
  QPixmap attIco(":/img/attack.png");
  attIco = attIco.scaled(40,40, Qt::KeepAspectRatio);
  QPixmap masIco(":/img/master.png");
  masIco = masIco.scaled(40,40, Qt::KeepAspectRatio);
  QPixmap evoIco(":/img/evo.png");
  evoIco = evoIco.scaled(40,40, Qt::KeepAspectRatio);
  QPixmap conIco(":/img/confused.png");
  conIco = conIco.scaled(40,40, Qt::KeepAspectRatio);
  insType->addItem(InsertView::DEFENSE);
  insType->setItemIcon(0, defIco);
  insType->addItem(InsertView::ATTACK);
  insType->setItemIcon(1, attIco);
  insType->addItem(InsertView::MASTER);
  insType->setItemIcon(2, masIco);
  insType->addItem(InsertView::EVOLUTION);
  insType->setItemIcon(3, evoIco);
  insType->addItem(InsertView::CONFUSED);
  insType->setItemIcon(4, conIco);
  insType->setEditable(false);

  addBtn->setToolTip("Opens a new window to insert a new Norvarad");

  QWidget* insWid = new QWidget(optWidget);
  QHBoxLayout* insLay = new QHBoxLayout(insWid);
  insLay->addWidget(insType, 0, Qt::AlignCenter);
  insLay->addWidget(addBtn, 0, Qt::AlignCenter);
  insWid->setLayout(insLay);

  QWidget* simWid = new QWidget(optWidget);
  QGridLayout* simLayout = new QGridLayout(simWid);
  actionValue->setRange(0,10000);
  actionValue->setDecimals(2);
  simLayout->addWidget(actionValue,1,0);
  simLayout->addWidget(simAttBtn,0,1);
  simLayout->addWidget(simDefBtn,1,1);
  simWid->setLayout(simLayout);

  optLayout->addWidget(insWid, 0, Qt::AlignHCenter | Qt::AlignTop);
  optLayout->addWidget(removeBtn, 0, Qt::AlignHCenter | Qt::AlignCenter);
  optLayout->addWidget(simWid, 0, Qt::AlignHCenter | Qt::AlignBottom);

  optWidget->setLayout(optLayout);

  // make layouts
  QWidget* contentWidget = new QWidget(this);
  QHBoxLayout* contentLayout = new QHBoxLayout(contentWidget);
  contentLayout->addWidget(list, 0);
  contentLayout->addWidget(optWidget, 0);
  contentWidget->setLayout(contentLayout);

  QWidget* searchWidget = new QWidget(this);
  QHBoxLayout* searchLayout = new QHBoxLayout(searchWidget);
  searchFilters->addItem(QString(Model::searchName));
  searchFilters->addItem(QString(Model::searchType));
  searchFilters->addItem(QString(Model::searchValueMajor));
  searchFilters->addItem(QString(Model::searchValueMinor));
  doubleValidator = new QDoubleValidator(searchWidget);
  doubleValidator->setNotation(QDoubleValidator::StandardNotation);
  searchInput->setPlaceholderText("Search...");
  searchInput->setClearButtonEnabled(true);
  searchLayout->addWidget(searchInput, 0);
  searchLayout->addWidget(searchFilters, 0);
  searchWidget->setLayout(searchLayout);
  searchWidget->setFixedHeight(50);

  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(searchWidget);
  mainLayout->addWidget(contentWidget);

  proxy = new ProxyModelAdapter(this, searchFilters);
  proxy->setSourceModel(adapter);
  list->setModel(proxy);

  // connects
  connect(addBtn, SIGNAL(clicked()), this, SLOT(insert()));
  connect(removeBtn, SIGNAL(clicked()), this, SLOT(removeNorvarad()));
  connect(simAttBtn, SIGNAL(clicked()), this, SLOT(simulateAttack()));
  connect(simDefBtn, SIGNAL(clicked()), this, SLOT(simulateDefense()));
  connect(searchInput, SIGNAL(textChanged(const QString&)), this, SLOT(textFilterChanged()));
  connect(searchFilters, SIGNAL(currentTextChanged(const QString&)), this, SLOT(textFilterChanged()));

  textFilterChanged();
  setLayout(mainLayout);
}

QSize CentralWidget::sizeHint() const
{
  return (QSize(850, 500));
}

void CentralWidget::removeNorvarad()
{
  const QModelIndexList selection = list->selectionModel()->selectedIndexes();
  if(selection.size() > 0)
    proxy->removeRows(selection.at(0).row(), 1);
}

void CentralWidget::insert()
{
  InsertView* insView = new InsertView(this, insType->currentText(), list, adapter, proxy);
  insView->exec();
}

void CentralWidget::simulateAttack()
{
  const QModelIndexList selection = list->selectionModel()->selectedIndexes();
  if(selection.size() > 0)
  {
    double aux = adapter->performAttack(selection.at(0));
    QMessageBox msgBox; // don't need parent because it's in stack
    std::ostringstream oss;
    std::string msg = "Attack value: ";
    oss << msg << aux;
    msgBox.setText(QString::fromStdString(oss.str()));
    msgBox.exec();
  }
}

void CentralWidget::simulateDefense()
{
  const QModelIndexList selection = list->selectionModel()->selectedIndexes();
  if(selection.size() > 0)
  {
    double aux = adapter->performDefense(selection.at(0), actionValue->value());
    QMessageBox msgBox; // don't need parent because it's in stack
    std::ostringstream oss;
    std::string msg = "Damage taken: ";
    oss << msg << aux;
    msgBox.setText(QString::fromStdString(oss.str()));
    msgBox.exec();
  }
}

void CentralWidget::textFilterChanged() {
  // toDouble() must be used only on valid numeric strings
  if ( searchFilters->currentText() == Model::searchValueMajor ||
        searchFilters->currentText() == Model::searchValueMinor )
  {
    searchInput->setValidator(doubleValidator);
    if ( searchInput->hasAcceptableInput() )
    {
      proxy->setFilterValue(searchInput->text().toDouble());
    }
    else
    {
      // reset input field
      searchInput->clear();
      proxy->setFilterValue(0);
    }
  }
  else
  {
    // remove validator
    searchInput->setValidator(nullptr);
  }

  QRegExp regex(searchInput->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
  proxy->setFilterRegExp(regex);
}

void CentralWidget::saveAction()
{
  QMessageBox msgBox; // don't need parent because it's in stack

  QString fileName = QFileDialog::getSaveFileName(this, "Choose XML file", "", "XML (*.xml)");

  if ( !fileName.isEmpty() && adapter->doSaveToFile(fileName) )
  {
    msgBox.setText(QString::fromStdString("Save OK"));
  }
  else
  {
    msgBox.setText(QString::fromStdString("Error!"));
  }
  msgBox.exec();
}

void CentralWidget::loadAction()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Choose XML file", "", "XML (*.xml)");

  if ( !fileName.isEmpty() )
  {
    adapter->doLoadFromFile(fileName);
  }
}
