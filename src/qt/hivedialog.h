// Copyright (c) 2011-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_HIVEDIALOG_H
#define BITCOIN_QT_HIVEDIALOG_H

#include <qt/guiutil.h>

#include <QDialog>
#include <QHeaderView>
#include <QItemSelection>
#include <QKeyEvent>
#include <QMenu>
#include <QPoint>
#include <QVariant>

class PlatformStyle;
class ClientModel;
class WalletModel;

namespace Ui {
    class HiveDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

class HiveDialog : public QDialog
{
    Q_OBJECT

public:
    enum ColumnWidths {
        CREATED_COLUMN_WIDTH = 100,
        COUNT_COLUMN_WIDTH = 60,
        STATUS_COLUMN_WIDTH = 85,
        BLOCKS_LEFT_COLUMN_WIDTH = 65,
        BLOCKS_FOUND_COLUMN_WIDTH = 85,
        TIME_LEFT_COLUMN_WIDTH = 135,
        COST_COLUMN_WIDTH = 90,
        REWARDS_COLUMN_WIDTH = 90,
        PROFIT_COLUMN_WIDTH = 90,
        HIVE_COL_MIN_WIDTH = 40
    };

    explicit HiveDialog(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~HiveDialog();

    void setClientModel(ClientModel *_clientModel);
    void setModel(WalletModel *model);

public Q_SLOTS:
    void updateData(bool forceGlobalSummaryUpdate = false);
    
protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::HiveDialog *ui;
    GUIUtil::TableViewLastColumnResizingFixer *columnResizingFixer;
    ClientModel *clientModel;
    WalletModel *model;
    const PlatformStyle *platformStyle;
    CAmount beeCost, totalCost;
    int immature, mature, dead, blocksFound;
    CAmount rewardsPaid, cost, profit;
    CAmount potentialRewards, projectedReturnPerBee;
    int lastGlobalCheckHeight;
    virtual void resizeEvent(QResizeEvent *event);

    void updateTotalCostDisplay();

private Q_SLOTS:
    void on_createBeesButton_clicked();
    void on_beeCountSpinner_valueChanged(int i);
    void on_includeDeadBeesCheckbox_stateChanged();
    void updateDisplayUnit();
    void on_retryGlobalSummaryButton_clicked();
    void on_refreshGlobalSummaryButton_clicked();
};

#endif // BITCOIN_QT_HIVEDIALOG_H
