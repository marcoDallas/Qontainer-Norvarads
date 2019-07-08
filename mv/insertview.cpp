#include "insertview.h"

const QString InsertView::DEFENSE = "Defense";
const QString InsertView::ATTACK = "Attack";
const QString InsertView::MASTER = "Master";
const QString InsertView::EVOLUTION = "Evolution";
const QString InsertView::CONFUSED = "Confused";

const double InsertView::MAX_HEALTH_VALUE = 1000;
const double InsertView::MAX_ATTACK_VALUE = 1000;
const int InsertView::MAX_ARMOR_VALUE = 85;

InsertView::InsertView(QWidget *parent, QString option, ListView* list,
                       ListModelAdapter* adapter, ProxyModelAdapter* proxy) :
  QDialog (parent), list(list), adapter(adapter), proxy(proxy)
{
  type = option;

  setFixedSize(400,300);

  // make layout
  QGridLayout* insLayout = new QGridLayout(this);
  // name input
  QLabel* nameLabel = new QLabel("Name",this);
  nameLine = new QLineEdit(this);
  // health input
  QLabel* healthLabel = new QLabel("Health [0-1000]:",this);
  healthLine = new QDoubleSpinBox(this);
  healthLine->setRange(0,MAX_HEALTH_VALUE);
  healthLine->setDecimals(2);
  // add to layout
  int row = 0;
  insLayout->addWidget(nameLabel,row,0);
  insLayout->addWidget(nameLine,row++,1);
  insLayout->addWidget(healthLabel,row,0);
  insLayout->addWidget(healthLine,row++,1);

  if (type == DEFENSE || type == MASTER || type == EVOLUTION)
  {
    QLabel* armorLabel = new QLabel("Armor [0-85]:",this);
    armorLine = new QSpinBox(this);
    armorLine->setRange(0,MAX_ARMOR_VALUE);
    insLayout->addWidget(armorLabel,row,0);
    insLayout->addWidget(armorLine,row++,1);
  }
  if (type == ATTACK || type == MASTER || type == CONFUSED)
  {
    QLabel* attackLabel = new QLabel("Attack [0-1000]:",this);
    attackLine = new QDoubleSpinBox(this);
    attackLine->setRange(0,MAX_ATTACK_VALUE);
    attackLine->setDecimals(2);
    insLayout->addWidget(attackLabel,row,0);
    insLayout->addWidget(attackLine,row++,1);
  }

  QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                       | QDialogButtonBox::Cancel, this);
  insLayout->addWidget(buttonBox,row,0,1,2);

  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
  setLayout(insLayout);
}

void InsertView::accept()
{
  // create the new Norvarad
  DeepPtr<Norvarad> norv = nullptr; // will allow deep copies down below
  if (type == DEFENSE)
  {
    NvdDefense nvd = NvdDefense(healthLine->value(),nameLine->text().toStdString(),static_cast<percentage>(armorLine->value()));
    norv = &nvd;
  }
  else if (type == ATTACK)
  {
    NvdAttack nvd = NvdAttack(healthLine->value(),nameLine->text().toStdString(),attackLine->value());
    norv = &nvd;
  }
  else if (type == MASTER)
  {
    NvdMaster nvd = NvdMaster(healthLine->value(),nameLine->text().toStdString(),attackLine->value(),static_cast<percentage>(armorLine->value()));
    norv = &nvd;
  }
  else if (type == EVOLUTION)
  {
    NvdDEvo nvd = NvdDEvo(healthLine->value(),nameLine->text().toStdString(),static_cast<percentage>(armorLine->value()));
    norv = &nvd;
  }
  else if (type == CONFUSED)
  {
    NvdAConfused nvd = NvdAConfused(healthLine->value(),nameLine->text().toStdString(),attackLine->value());
    norv = &nvd;
  }

  if (norv != nullptr)
  {
    // add new Norvarad to container
    adapter->setupInsert(*norv);
    proxy->insertRows(proxy->rowCount(), 1);

    list->clearSelection();
    list->selectionModel()->clearCurrentIndex();
    list->selectionModel()->select(proxy->index(adapter->rowCount() - 1, 0), QItemSelectionModel::Select);
  }

  QDialog::accept();
}
