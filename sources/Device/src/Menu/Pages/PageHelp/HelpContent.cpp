#include "defines.h"
#include "Settings/Settings.h"
#include "Display/Primitives.h"
#include "Display/Font/Font.h"
#include "Display/Grid.h"
#include "Display/Painter.h"
#include "Hardware/Timer.h"
#include "Utils/Math.h"
#include "Menu/Pages/Include/HelpContentPages.h"
#include "Menu/Pages/Include/HelpContent.h"


using namespace Display::Primitives;



static int currentParagraph = 0;   // ���� TypePage(currentPage) == TypePage_Content, �� ��������� �� ������� ������ ����������
static const PageHelpContent *currentPage = &helpMain;


static const int WIDTH = 295;



static void DrawPageContent()
{
    int y = 50;

    Text(currentPage->Title()).DrawInCenterRect(0, y, WIDTH, 10);

    int numPage = 0;

    y += 40;

    while(currentPage->pages[numPage])
    {
        Page *page = (Page *)currentPage->pages[numPage];
        const char *title = page->Title().CString();
        if(currentParagraph == numPage)
        {
            Text(title).DrawInCenterRectOnBackground(0, y, WIDTH, 10, Color::BACK, 2, Color::FILL);
        }
        else
        {
            Text(title).DrawInCenterRect(0, y, WIDTH, 10, Color::FILL);
        }
        y += 16;
        numPage++;
    }
}


static void DrawPageDescription()
{
    Text(currentPage->Title()).DrawInCenterRect(0, 3, WIDTH, 10);
    Text(currentPage->Hint()).DrawInRectWithTransfers(2, 15, WIDTH - 5, 240);
}


void HelpContent::Draw()
{
    Region(319 - Grid::Right(), 20).Fill(Grid::Right(), 0, Color::BACK);
    Region(319 - Grid::Right(), 21).Fill(Grid::Right(), 219);
    Region(WIDTH, 237).Fill(1, 1);
    Rectangle(WIDTH + 1, 239).Draw(1, 0, Color::FILL);   /** \todo ����� ���������, ������ ���. ���������� �������� ������ ���� ������ ����
                                                                0, 0, �� � ����� ������ ����� ������������ ������ �� ����� */

    /*
    uint16 *addr1 = (uint16 *)(0x08000000 + (rand() % 65535));
    uint8 *addr2 = (uint8 *)(0x08000000 + (rand() % 65535));

    Color::FILL.SetAsCurrent();
    for (int i = 0; i < 10000; i++)
    {
        Painter::SetPoint((*addr1) % WIDTH, Math_LimitationInt(*addr2, 0, 239));
        addr1++;
        addr2++;
    }
    */

    if(currentPage->type == TypePage_Content)
    {
        DrawPageContent();
    }
    else if(currentPage->type == TypePage_Description)
    {
        DrawPageDescription();
    }
    else
    {
        // ����� ��������� ��� ������
    }
}


static int NumParagraphs(const PageHelpContent *page)
{
    int retValue = 0;
    while(page->pages[retValue])
    {
        retValue++;
    }
    return retValue;
}


void HelpContent::NextParagraph()
{
    if(currentPage->type == TypePage_Content)
    {
        Math::CircleIncrease<int>(&currentParagraph, 0, NumParagraphs(currentPage) - 1);
    }
}


void HelpContent::PrevParagraph()
{
    if(currentPage->type == TypePage_Content)
    {
        Math::CircleDecrease<int>(&currentParagraph, 0, NumParagraphs(currentPage) - 1);
    }
}


void HelpContent::EnterParagraph()
{
    if(currentPage->type == TypePage_Content)
    {
        currentPage = (const PageHelpContent *)currentPage->pages[currentParagraph];
    }
    currentParagraph = 0;
}


void HelpContent::LeaveParagraph()
{
    currentParagraph = 0;
    if(currentPage->parent)
    {
        currentPage = (const PageHelpContent *)currentPage->parent;
    }
}


bool HelpContent::LeaveParagraphIsActive()
{
    return currentPage->parent != 0;
}


bool HelpContent::EnterParagraphIsActive()
{
    return currentPage->type == TypePage_Content;
}
