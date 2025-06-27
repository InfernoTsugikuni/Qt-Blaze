#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

// Configuration struct for window appearance
struct WindowConfig {
    int width = 800;
    int height = 600;
    int borderRadius = 15;
    int borderWidth = 1;
    QColor backgroundColor = QColor("#333");
    QColor borderColor = QColor("#757575");
    bool fixedSize = false;
    
    // Title bar config
    bool showTitleBar = true;
    QString windowTitle = "Custom Window";
    QColor titleBarColor = QColor("#242424");
    QColor titleTextColor = QColor("#ff6b00");
    QString titleFontSize = "16px";
    int titleBarHeight = 30;
    
    // Button assets (optional - will use default styles if empty)
    QString minimizeIcon = "";
    QString minimizeHoverIcon = "";
    QString closeIcon = "";
    QString closeHoverIcon = "";
};

// Custom TitleBar class
class CustomTitleBar : public QWidget {
    Q_OBJECT
public:
    explicit CustomTitleBar(QWidget* parent = nullptr, const WindowConfig& config = WindowConfig{})
        : QWidget(parent), m_config(config) {
        setFixedHeight(config.titleBarHeight);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        createUI();
    }

    void setTitle(const QString& title) {
        if (titleLabel) {
            titleLabel->setText(title);
        }
    }

signals:
    void minimizeClicked();
    void closeClicked();
    void titleBarDragged(const QPoint& delta);

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            offset = event->globalPosition().toPoint();
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (event->buttons() & Qt::LeftButton) {
            QPoint delta = event->globalPosition().toPoint() - offset;
            offset = event->globalPosition().toPoint();
            emit titleBarDragged(delta);
        }
    }

    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        QPainterPath path;
        path.moveTo(0, m_config.borderRadius);
        path.quadTo(0, 0, m_config.borderRadius, 0);
        path.lineTo(width() - m_config.borderRadius, 0);
        path.quadTo(width(), 0, width(), m_config.borderRadius);
        path.lineTo(width(), height());
        path.lineTo(0, height());
        path.closeSubpath();

        p.fillPath(path, m_config.titleBarColor);
        p.setPen(QPen(m_config.borderColor, 1));
        p.drawLine(0, height() - 1, width(), height() - 1);
    }

private:
    WindowConfig m_config;
    QLabel* titleLabel = nullptr;
    QPushButton* minimizeButton = nullptr;
    QPushButton* closeButton = nullptr;
    QPoint offset;

    void createUI() {
        titleLabel = new QLabel(m_config.windowTitle, this);
        titleLabel->setStyleSheet(QString("color: %1; font-size: %2; font-weight: bold;")
                                .arg(m_config.titleTextColor.name())
                                .arg(m_config.titleFontSize));

        minimizeButton = new QPushButton(this);
        minimizeButton->setFixedSize(18, 18);
        minimizeButton->setCursor(Qt::PointingHandCursor);
        
        QString minimizeStyle = "QPushButton { background-color: transparent; border: none; }";
        if (!m_config.minimizeIcon.isEmpty()) {
            minimizeStyle = QString(
                "QPushButton {"
                "    background-image: url(%1);"
                "    background-color: transparent;"
                "    border: none;"
                "}").arg(m_config.minimizeIcon);
            
            if (!m_config.minimizeHoverIcon.isEmpty()) {
                minimizeStyle += QString(
                    "QPushButton:hover {"
                    "    background-image: url(%1);"
                    "}").arg(m_config.minimizeHoverIcon);
            }
        } else {
            // Default minimize button style
            minimizeStyle = 
                "QPushButton {"
                "    background-color: #666;"
                "    border: none;"
                "    color: white;"
                "}"
                "QPushButton:hover {"
                "    background-color: #888;"
                "}";
            minimizeButton->setText("−");
        }
        minimizeButton->setStyleSheet(minimizeStyle);
        connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeClicked);

        closeButton = new QPushButton(this);
        closeButton->setFixedSize(18, 18);
        closeButton->setCursor(Qt::PointingHandCursor);
        
        QString closeStyle = "QPushButton { background-color: transparent; border: none; }";
        if (!m_config.closeIcon.isEmpty()) {
            closeStyle = QString(
                "QPushButton {"
                "    background-image: url(%1);"
                "    background-color: transparent;"
                "    border: none;"
                "}").arg(m_config.closeIcon);
            
            if (!m_config.closeHoverIcon.isEmpty()) {
                closeStyle += QString(
                    "QPushButton:hover {"
                    "    background-image: url(%1);"
                    "}").arg(m_config.closeHoverIcon);
            }
        } else {
            // Default close button style
            closeStyle = 
                "QPushButton {"
                "    background-color: #d32f2f;"
                "    border: none;"
                "    color: white;"
                "}"
                "QPushButton:hover {"
                "    background-color: #f44336;"
                "}";
            closeButton->setText("×");
        }
        closeButton->setStyleSheet(closeStyle);
        connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeClicked);

        auto* layout = new QHBoxLayout(this);
        layout->setContentsMargins(10, 0, 10, 0);
        layout->addWidget(titleLabel);
        layout->addStretch();
        layout->addWidget(minimizeButton);
        layout->addWidget(closeButton);
        setLayout(layout);
    }
};

// Function to setup a custom frameless window with rounded corners
inline void setupCustomWindow(QMainWindow* window, const WindowConfig& config = WindowConfig{}) {
    if (!window) return;
    
    // Set window flags for frameless, translucent window
    window->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    window->setAttribute(Qt::WA_TranslucentBackground);
    
    // Set window size
    if (config.fixedSize) {
        window->setFixedSize(config.width, config.height);
    } else {
        window->resize(config.width, config.height);
    }
    
    window->setFocusPolicy(Qt::StrongFocus);
}

// Base class that handles everything automatically
class CustomWindowBase : public QMainWindow {
    Q_OBJECT

public:
    explicit CustomWindowBase(QWidget *parent = nullptr, const WindowConfig& config = WindowConfig{})
        : QMainWindow(parent), m_config(config) {
        setupCustomWindow(this, config);
        setupUI();
    }

    void setWindowConfig(const WindowConfig& config) {
        m_config = config;
        if (m_titleBar) {
            m_titleBar->setTitle(config.windowTitle);
        }
        update();
    }

    void setWindowTitle(const QString& title) {
        if (m_titleBar) {
            m_titleBar->setTitle(title);
        }
        QMainWindow::setWindowTitle(title);
    }

    CustomTitleBar* getTitleBar() const {
        return m_titleBar;
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        if (!event) return;

        try {
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            QRectF fullRect = rect().adjusted(
                0.5 * m_config.borderWidth,
                0.5 * m_config.borderWidth,
                -0.5 * m_config.borderWidth,
                -0.5 * m_config.borderWidth
            );

            QPainterPath fullPath;
            fullPath.addRoundedRect(fullRect, m_config.borderRadius, m_config.borderRadius);
            
            // Fill background
            painter.fillPath(fullPath, m_config.backgroundColor);
            
            // Draw border (skip the title bar area)
            painter.save();
            if (m_titleBar && m_config.showTitleBar) {
                int clipY = m_titleBar->height();
                painter.setClipRect(QRectF(0, clipY, width(), height()));
            }
            painter.setPen(QPen(m_config.borderColor, m_config.borderWidth));
            painter.drawPath(fullPath);
            painter.restore();
            
        } catch (const std::exception& e) {
            qDebug() << "Exception in paintEvent:" << e.what();
        }
    }

    void resizeEvent(QResizeEvent* event) override {
        if (!event) return;

        try {
            // Create rounded mask
            QPixmap pixmap(size());
            pixmap.fill(Qt::transparent);

            QPainter painter(&pixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setBrush(Qt::black);
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(rect(), m_config.borderRadius, m_config.borderRadius);
            painter.end();

            setMask(pixmap.mask());
        } catch (const std::exception& e) {
            qDebug() << "Exception in resizeEvent:" << e.what();
        }

        QMainWindow::resizeEvent(event);
    }

private slots:
    void onTitleBarDragged(const QPoint &delta) {
        move(pos() + delta);
    }

    void onMinimizeClicked() {
        showMinimized();
    }

    void onCloseClicked() {
        close();
    }

private:
    WindowConfig m_config;
    CustomTitleBar* m_titleBar = nullptr;

    void setupUI() {
        // Create central widget and layout
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Add title bar if enabled
        if (m_config.showTitleBar) {
            m_titleBar = new CustomTitleBar(this, m_config);
            connect(m_titleBar, &CustomTitleBar::minimizeClicked, this, &CustomWindowBase::onMinimizeClicked);
            connect(m_titleBar, &CustomTitleBar::closeClicked, this, &CustomWindowBase::onCloseClicked);
            connect(m_titleBar, &CustomTitleBar::titleBarDragged, this, &CustomWindowBase::onTitleBarDragged);
            layout->addWidget(m_titleBar);
        }

        layout->addStretch();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        setCentralWidget(centralWidget);
    }
};

#endif // CUSTOMWINDOW_H
