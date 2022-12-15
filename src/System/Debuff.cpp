//
// Created by cyril on 03/07/2022.
//

#include "Debuff.h"
#include "../main.h"

void Debuff::setParams()
{
    switch (type_) {
    case DEBUFF_NONE:
        name_ = "none";
        iconPath_ = "";
        desc_ = "";
        drawIcon_ = false;
        break;
    case DEBUFF_ROOT:
        name_ = "Root";
        iconPath_ = "Images/Debuff/root.png";
        desc_ = "Immobilize the target.";
        color_.addTarget("Root", 0xEE9B00FF);
        drawIcon_ = true;
        break;
    case DEBUFF_CRITICAL:
        name_ = "Weakness";
        iconPath_ = "Images/Debuff/weakness.png";
        desc_ = "The target enters in a weakened state. While weakened, the target dies if the target is weakened again.";
        color_.addTarget("Weekness", 0xAE2012FF);
        drawIcon_ = true;
        break;
    case DEBUFF_SUDDENDEATH:
        name_ = "Sudden Death";
        iconPath_ = "Images/Debuff/suddendeath.png";
        desc_ = "The map ends at the end of the countdown.";
        color_.addTarget("Sudden Death", 0xFFFFFF00);
        drawIcon_ = true;
        break;
    case DEBUFF_MASK1:
        name_ = "Unscrupulous Cheers";
        iconPath_ = "Images/Debuff/mask1.png";
        desc_ = "The unscrupulous cheers were all fake. If <Unscrupulous Cheers> is applied again, inflicts <Sudden Death> to the target.";
        drawIcon_ = true;
        break;
    case DEBUFF_MASK2:
        name_ = "Fake Feelings";
        iconPath_ = "Images/Debuff/mask2.png";
        desc_ = "Your seeping jealousy drips out. If <Fake Feelings> is applied again, inflicts <Sudden Death> to the target.";
        drawIcon_ = true;
        break;

    case DEBUFF_HAATO:
        name_ = "Haato";
        iconPath_ = "Images/Debuff/haato.png";
        desc_ = "Kuruado no Haato! If <Haato> is applied again, inflicts <Sudden Death> to the target.";
        drawIcon_ = true;
        break;
    case DEBUFF_GAADO:
        name_ = "Gaado";
        iconPath_ = "Images/Debuff/gaado.png";
        desc_ = "Kono Gaado! If <Gaado> is applied again, inflicts <Sudden Death> to the target.";
        drawIcon_ = true;
        break;

    case DEBUFF_EYE1:
        name_ = "First Eye";
        iconPath_ = "Images/Debuff/firsteye.png";
        desc_ = "It's asleep.";
        drawIcon_ = true;
        break;

    case DEBUFF_EYE2:
        name_ = "Second Eye";
        iconPath_ = "Images/Debuff/secondeye.png";
        desc_ = "It's waking.";
        drawIcon_ = true;
        break;

    case DEBUFF_EYE3:
        name_ = "Third Eye";
        iconPath_ = "Images/Debuff/thirdeye.png";
        desc_ = "It's watching!";
        drawIcon_ = true;
        break;

    case DEBUFF_EYER:
        name_ = "Third Eyer";
        iconPath_ = "Images/Debuff/thirdeyer.png";
        desc_ = "Mieru mieru! If <Thrid Eye> is not applied, inflicts <Sudden Death> to the target.";
        drawIcon_ = true;
        break;

    }
}

Debuff::Debuff() {
    type_ = DEBUFF_NONE;
    end_ = 0;
    notif_ = -1;

    shape_.setRadius(2*BASE_PLAYER_RADIUS);
    shape_.setOrigin(2*BASE_PLAYER_RADIUS, 2*BASE_PLAYER_RADIUS);

    color_.addTarget("none", 0xFFFFFF00);
    color_.setSpeed({0.25, 0.25, 0.25, 0.25});
    color_.initCurrent("none");
}

bool Debuff::update(sf::Time elapsed, float beat) {
    timer_ += elapsed;

    if (timer_.asSeconds() > 1.5) {
        startDraw_ = false;
        endDraw_ = false;
        notif_ = -1;
    }
        


    if(type_ != DEBUFF_NONE) {
        if (beat >= end_) {
            timer_ = sf::seconds(0);
            endDraw_ = true;
            if (type_ == DEBUFF_SUDDENDEATH) {
                if (!IS_SERVER) {
                    type_ = DEBUFF_NONE;
                    setParams();
                }
                return true;
            }
            type_ = DEBUFF_NONE;
            setParams();
        }
    }

    color_.setCurrentTarget(name_);

    color_.updateColor(elapsed);
    return false;
}

void Debuff::draw(sf::RenderTarget &window, sf::Vector2f position) {
    shape_.setFillColor(color_.getCurrentColor());
    shape_.setPosition(position);
    window.draw(shape_);
}

void Debuff::notification(sf::RenderTarget& window, sf::Vector2f position)
{
    if (!oldDrawIcon_)
        return;
    if (!startDraw_ && !endDraw_)
        return;

    sf::Color color = sf::Color::White;

    float t = timer_.asSeconds();

    float deltaX = -100+170 * (1 - std::exp(-5*t));
    float deltaY = -25 - notif_ * 60;
    
    std::string mod = "";

    if (startDraw_) mod = "+ ";
    if (endDraw_) mod = "- ";


    color.a = - 255 * 1.78 *t * (t - 1.5);

    sf::Sprite icon;
    icon.setTexture(RessourceLoader::getTexture(drawPath_));
    icon.setScale(0.25, 0.25);

    icon.setPosition(position.x + deltaX, position.y + deltaY);
    icon.setColor(color);

    sf::Text text;
    text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    text.setCharacterSize(35);
    text.setString(mod + drawName_);
    text.setFillColor(color);

    text.setPosition(position.x + deltaX + 60, position.y + deltaY);

    window.draw(icon);
    window.draw(text);
}

void Debuff::apply(DebuffType type, float end) {
    type_ = type;
    end_ = end;

    startDraw_ = true;

    setParams();

    drawName_ = name_;
    drawDesc_ = desc_;
    drawPath_ = iconPath_;
    oldDrawIcon_ = drawIcon_;
}

DebuffType Debuff::type() {
    return type_;
}

bool Debuff::getDrawIcon()
{
    return drawIcon_;
}

std::string Debuff::getName()
{
    return drawName_;
}

std::string Debuff::getDesc()
{
    return drawDesc_;
}

void Debuff::set(DebuffType type, float end)
{
    type_ = type;
    end_ = end;

    setParams();
}

void Debuff::clense() {
    type_ = DEBUFF_NONE;
}

bool Debuff::isNotif()
{
    return oldDrawIcon_ && (startDraw_ || endDraw_);
}

void Debuff::setNotif(int val)
{
    if (notif_ == -1)
        notif_ = val;
}

int Debuff::getNotif()
{
    return notif_;
}

std::string Debuff::getIcon()
{
    return iconPath_;
}

float Debuff::getEnd()
{
    return end_;
}
