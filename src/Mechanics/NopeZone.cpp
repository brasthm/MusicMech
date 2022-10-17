#include "NopeZone.h"

#include "../System/Random.h"

void NopeZone::updatePosition(EntityManager& entityManager)
{
    position_ = entityManager.getPosition(target_);

    base_.setPosition({ position_.x, position_.y });
    rect_.left = position_.x;
    rect_.top = position_.y;
    playerIndicator_.updatePosition(position_);
}

void NopeZone::setColor()
{
    sf::Uint32 outlineColor = 0, fillColorPlayerIndicator = 0, fillColor = 0, fillColorFailed = 0, approachColor = 0;

    if (isShare_) {
        outlineColor = 0xDAFB93FF;
        fillColor = 0x89C17EFF;
        fillColorFailed = 0x427538FF;
        fillColorPlayerIndicator = 0xDAFB9300;
        approachColor = 0x79CE1BFF;
    }
    else {
        outlineColor = 0xFFD5CBFF;
        fillColor = 0xB64F38FF;
        fillColorFailed = 0x781F0BFF;
        fillColorPlayerIndicator = 0xFFD5CB00;
        approachColor = 0xD35227FF;
    }

    backColor_.setSpeed({ 0.1, 0.1, 0.1, 0.5 });

    playerIndicator_.setOutlineColor(outlineColor);
    playerIndicator_.setFillColor(fillColorPlayerIndicator);
    backColor_.addTarget("good", fillColor);
    backColor_.addTarget("failed", fillColorFailed);
    backColor_.addTarget("hightlight", 0xe8bb00ff);

    backColor_.initCurrent("good");
    base_.setOutlineColor(sf::Color(outlineColor));
}

NopeZone::NopeZone(float beat, float width, float height, int nbShare, float active, const Target& target) :
    target_(target),
    playerIndicator_({}, sf::Vector2f(width * 0.5f, height *0.5f), nbShare,
        width * 0.095f, width * 0.02f)
{
    beat_ = beat;
    width_ = width;
    height_ = height;
    draw_ = false;

    nbIn_ = 0;
    nbShare_ = nbShare;

    isShare_ = nbShare != 0;
    active_ = active;

    setColor();


    base_.setSize({width_, height_});
    base_.setOutlineThickness(5);

    rect_.width = width;
    rect_.height = height;

    Mechanic::setSoundName("Sound/normal-hitnormal.wav");

    drawPriority_ = -10;

    highlightTimer_ = sf::seconds(0);
    highlight_ = false;
}

void NopeZone::onDraw(const sf::Time& elapsed, sf::RenderTarget& window)
{
    if (draw_) {
        if (isFailed()) {
            backColor_.setSpeed({ 0.5, 0.5, 0.5, 0.5 });
            highlightTimer_ += elapsed;
            backColor_.updateColor(elapsed);
            if (highlightTimer_.asSeconds() > 1) {
                highlightTimer_ = sf::seconds(0);
                backColor_.setCurrentTarget(highlight_ ? "failed" : "hightlight");
                highlight_ = !highlight_;
            }
        }
        base_.setFillColor(backColor_.getCurrentColor());
        base_.setPosition(position_ + shift_);
        base_.setRotation(rotation_);
        window.draw(base_);
        playerIndicator_.draw(window);
    }
}

void NopeZone::onCheck(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities)
{
    nbIn_ = 0;

    //std::cout << entities.getSizePlayers() << std::endl;
    for (int i = 0; i < entities.getSizePlayers(); i++) {
        Target t(TARGET_ENTITY, TARGET_PLAYERS, i);
        if (!entities.getActive(t))
            break;

        bool good = rect_.contains(entities.getPosition(t));

        if (good) {
            nbIn_++;
        }
    }

    passed_ = nbIn_ == nbShare_;

    if (!passed_ && !pause_) {
        float mercy = 0;//active_ > 16 ? 4 : 2;
        if (currentBeat > beat_ - active_ + mercy)
            timer_ += elapsed;
        if (timer_ >= sf::seconds(2.5))
            checked_ = true;
        if (timer_ >= sf::seconds(1)) {
            vibrate_ += elapsed;
            if (vibrate_ >= sf::milliseconds(50)) {
                shift_.x = Random::randint(-10, 10);
                shift_.y = Random::randint(-10, 10);
                rotation_ = Random::randint(-3, 3);
                vibrate_ = sf::seconds(0);
            }
        }
        else {
            shift_.x = 0;
            shift_.y = 0;
            rotation_ = 0;
        }
    }
    else {
        timer_ = sf::seconds(0);
        shift_.x = 0;
        shift_.y = 0;
        rotation_ = 0;
    }


    if (passed_ || earlypassed_) {
        backColor_.setCurrentTarget("good");
    }
    else {
        backColor_.setCurrentTarget("failed");
    }
    backColor_.updateColor(elapsed);
    

    playerIndicator_.updateLight(nbIn_);
}

void NopeZone::onApproach(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities)
{
    if (target_.timing == TARGET_FOLLOW) {
        updatePosition(entities);
    }
}

void NopeZone::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    if (target_.timing == TARGET_ONBEAT) {
        updatePosition(entities);
    }
}

void NopeZone::onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    sf::Color color = base_.getFillColor();
    color = base_.getOutlineColor();
    color.a = 255 * (1 - currentPart);
    base_.setOutlineColor(color);

    backColor_.setSpeed({ 0.1, 0.1, 0.1, 0.5 });


    backColor_.setCurrentColor(3, 255 * (1 - currentPart));
    playerIndicator_.updateAlpha(currentPart);
}

void NopeZone::onInit(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    if (target_.timing == TARGET_ONINIT) {
        updatePosition(entities);
    }
}

void NopeZone::reset(float beat)
{
    setColor();

    base_.setPosition(position_.x, position_.y);
    timer_ = sf::seconds(0);


    Mechanic::reset(beat);
}

std::string NopeZone::toString()
{
    std::string res;

    res = "NOPEZONE," + std::to_string(beat_) + "," + std::to_string(nbShare_) + "," +
        std::to_string(width_) + "," + std::to_string(height_) + "," + std::to_string(active_) + ",";

    res += target_.to_string();

    return res;
}

void NopeZone::getTargetPos(std::vector<sf::Vector2f>& pos)
{
    pos.emplace_back(position_);
}

void NopeZone::setTargetPos(std::vector<sf::Vector2f>& pos)
{
    if (pos.size() != 1) {
        std::cout << "NopeZone::setTargetPos : pos vector is wrong size." << std::endl;
        return;
    }

    target_.type = TargetType::TARGET_POS;
    target_.pos = pos[0];
}

Mechanic* NopeZone::clone()
{
    return new NopeZone(*this);
}
