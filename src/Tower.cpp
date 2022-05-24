//
// Created by cyril on 21/05/2022.
//

#include "Tower.h"
#include "Utils.h"

Tower::Tower(float beat, sf::Vector2f position, float radius) :
    approachCircle_(position, radius + 10, 20, 0){
        position_ = position;
        beat_ = beat;
        radius_ = radius;
        draw_=false;

        nbIn_ = 0;
        nbShare_ = 1;

        float c = radius_ * 0.195;
        float g = radius_ * 0.1;

        float step = (SQRT2*c + SQRT2*g)/2;

        sf::Vector2f pos0(position_.x, position.y + radius_*0.6f);

        for(int i = 0; i < nbShare_; i++) {
            lights_.emplace_back();

            lights_.back().setFillColor(sf::Color(0xDAFB9300));
            lights_.back().setOutlineThickness(2);
            lights_.back().setOutlineColor(sf::Color(0xDAFB93FF));

            lights_.back().setSize({c, c});
            lights_.back().setRotation(45);


            if(i == 0) {
                lights_.back().setPosition(pos0.x , pos0.y);
            }
            else if(i == 1) {
                lights_.back().setPosition(pos0.x - step, pos0.y - step);
            }
            else if(i == 2) {
                lights_.back().setPosition(pos0.x + step, pos0.y - step);
            }
            else if(i == 3) {
                lights_.back().setPosition(pos0.x, pos0.y - 2 * step);
            }
        }


        newRadius_ = radius_;

        colorGood_ = sf::Color(0x89CA7EFF);
        colorFailed_ = sf::Color(0x427538FF);

        colorCurrent_ = Utils::RGBtoHSV(colorFailed_);
        colorTarget_ = colorCurrent_;

        speedColor_ = {10, 1, 5};


        base_.setRadius(radius_);
        base_.setPosition(position_.x - radius_, position_.y - radius_);

        base_.setOutlineThickness(5);
        base_.setOutlineColor(sf::Color(0xDAFB93FF));
        base_.setPointCount(100);

        Mechanic::setSoundName("Sound/normal-hitnormal.wav");
}

void Tower::draw(sf::RenderWindow &window) {
    if(draw_) {
        approachCircle_.draw(window);
        base_.setFillColor(Utils::HSVtoRGB(colorCurrent_));
        window.draw(base_);

        for(int i = 0; i < lights_.size(); i++) {
            window.draw(lights_[i]);
        }
    }

}

void Tower::update(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {

    if(beat_ > currentBeat && beat_ - currentBeat <= 4) {
        check(joueurs);
        Mechanic::updateColor(elapsed);

        if(currentPart > 0.66) {
            approachCircle_.setProportion(0.25 * (4 - (beat_ - currentBeat)) + 0.25*(currentPart - 0.66)/0.34);
        }
        draw_ = true;
    }
    else if(beat_ == currentBeat) {

        if(!checked_ && currentPart < 0.25) {
            check(joueurs);
            Mechanic::updateColor(elapsed);
        }

        if(!checked_ && passed_) {
            Mechanic::playSound();
            newRadius_ = radius_ * (1 + 0.5 * (1 - currentPart));

            checked_ = false;
        }

        approachCircle_.setProportion(1);

        sf::Color color = base_.getFillColor();
        color.a = 255*(1-currentPart);
        base_.setFillColor(color);

        color = base_.getOutlineColor();
        color.a = 255*(1-currentPart);
        base_.setOutlineColor(color);

        approachCircle_.setAlpha(255*(1-currentPart));


        base_.setRadius(newRadius_);
        base_.setPosition(position_.x - newRadius_, position_.y - newRadius_);
        approachCircle_.setDistance(newRadius_);

        float c = newRadius_ * 0.195;
        float g = newRadius_ * 0.1;

        float step = (SQRT2*c + SQRT2*g)/2;

        sf::Vector2f pos0(position_.x, position_.y + newRadius_*0.6f);

        for(int i = 0; i < nbShare_; i++) {
            lights_.emplace_back();

            color = lights_[i].getFillColor();
            if(color.a != 0) {
                color.a = 255*(1-currentPart);
                lights_[i].setFillColor(color);
            }

            color = lights_[i].getOutlineColor();
            color.a = 255*(1-currentPart);
            lights_[i].setOutlineColor(color);

            lights_[i].setSize({c, c});


            if(i == 0) {
                lights_[i].setPosition(pos0.x , pos0.y);
            }
            else if(i == 1) {
                lights_[i].setPosition(pos0.x - step, pos0.y - step);
            }
            else if(i == 2) {
                lights_[i].setPosition(pos0.x + step, pos0.y - step);
            }
            else if(i == 3) {
                lights_[i].setPosition(pos0.x, pos0.y - 2 * step);
            }
        }

    }
    else {
        draw_ = false;
    }

}

void Tower::check(std::vector<Joueur> &joueurs) {

    nbIn_ = 0;
    for(int  i = 0; i < joueurs.size(); i++) {
        bool good = Utils::distance(joueurs[i].getPos(), position_) < radius_;

        if(good) {
            nbIn_++;
        }

    }

    passed_ = nbIn_ == nbShare_;

    if(passed_) {
        Mechanic::setColorTarget(colorGood_);
    }
    else {
        Mechanic::setColorTarget(colorFailed_);
    }

    for(int i = 0; i < lights_.size(); i++) {
        sf::Color c = lights_[i].getFillColor();
        c.a = i < nbIn_ ? 255:0;
        lights_[i].setFillColor(c);
    }


}
