#include "Level.h"
#include <filesystem>

Level::Level(b2World& world, Physics& physics, Layout& layout, const std::string &file)
    : physics_(physics), layout_(layout), currentBird_(0), slingshot_({layout_.slingshotOffsetX, 575 })
{
    load(file);

    ground_ = std::make_unique<RectangleEntity>(world,
        sf::Vector2f(1.5f * layout_.windowWidth, layout_.groundHeight),
        sf::Vector2f(layout_.windowWidth / 2.f, layout_.windowHeight - layout_.groundHeight / 2.f),
        false);
    ground_->shape().setFillColor(sf::Color::Transparent);

}

Level::~Level()
{

}

sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t){
    return a + t * (b - a);
}

static std::filesystem::path getResourcePath(const std::string& filename)  {

    std::filesystem::path exePath = std::filesystem::current_path();
    std::filesystem::path resourcePath = exePath / "assets" / "textures" / filename;
    return resourcePath;
}

void Level::load(const std::string& file){
    //Parse file to create birds and so on

    birdTexture_.loadFromFile(getResourcePath("bird.png").string());
    birdTexture2_.loadFromFile(getResourcePath("bird2.png").string());
    pigTexture_.loadFromFile(getResourcePath("pig.png").string());
    bg_.loadFromFile(getResourcePath("ogbg.png").string());

    bgSprite_.setTexture(bg_);
    

    Block block(physics_.get_world(), sf::Vector2f(700.f, 618.f), sf::Vector2f(25.f, 200.f), false );
    Block block1(physics_.get_world(), sf::Vector2f(800.f, 618.f), sf::Vector2f(25.f, 200.f), false );
    Block block2(physics_.get_world(), sf::Vector2f(700.f, 418.f), sf::Vector2f(200.f, 25.f), false );
    castle_.add_block(block);
    castle_.add_block(block1);
    castle_.add_block(block2);

    birds_.emplace_back(physics_.get_world(), sf::Vector2f(100.f, 500.f),&birdTexture_,20);
    birds_.emplace_back(physics_.get_world(), sf::Vector2f(120.f, 500.f),&birdTexture2_,20);
    birds_.emplace_back(physics_.get_world(), sf::Vector2f(160.f, 500.f),&birdTexture_,20);
    enemies_.emplace_back(physics_.get_world(), sf::Vector2f(700.f, 500.f ),&pigTexture_);
    enemies_.emplace_back(physics_.get_world(), sf::Vector2f(900.f, 700.f ),&pigTexture_);

    for (auto& enemy : enemies_) {
        enemy.body()->GetUserData().pointer = reinterpret_cast<uintptr_t>(&enemy);
    }

    slingshot_.attach_bird(&birds_[currentBird_]);

}

void Level::update(float delta, Camera& camera){
    physics_.step(delta);

    for(auto& bird : birds_)
         bird.update(delta);
    
    castle_.update(delta);

    for (auto& enemy : enemies_) {
         enemy.update(delta);

      //  float speed = enemy.body()->GetLinearVelocity().Length();
       // if (speed > 0.8) {   
       //     enemy.kill();
       // }
    }

    camera.update(delta);

    auto& bird = birds_[currentBird_];
    b2Vec2 pos = bird.body()->GetPosition();

    bool outOfBounds = pos.y * layout_.scale > layout_.windowHeight;

    if (bird.body()->GetLinearVelocity().Length() < 0.2f && bird.launched() || outOfBounds) {
        bird.set_active(false);

        if (currentBird_ < birds_.size() -1 ) {
            currentBird_++;
            slingshot_.attach_bird(&birds_[currentBird_]);
            b2Vec2 pos = birds_[currentBird_].body()->GetPosition();
            camera.follow_bird({ pos.x * layout_.scale, 384.f + 25.f }); // y = screen height / 2

            camera.zoom_out();
        }
    }
}

void Level::render(sf::RenderWindow& window, Camera& camera){
    window.setView(camera.get_view());

    sf::Vector2u textureSize = bg_.getSize();

    bgSprite_.setOrigin(textureSize.x / 2.f, textureSize.y / 2.f -200);
    bgSprite_.setScale(1.3 , 1.3);
    
    window.draw(bgSprite_);

    ground_->render(window);
    for(auto& bird : birds_)
        bird.render(window);
    
    castle_.render(window);

    for(auto& enemy : enemies_)
        enemy.render(window);
    
    if (slingshot_.launched()) {
        b2Vec2 pos = birds_[currentBird_].body()->GetPosition();
        camera.follow_bird({pos.x * layout_.scale, layout_.windowHeight / 2.f + 25.f });
    }

    slingshot_.render(window);

}

bool Level::completed() const{
    for(const auto& enemy : enemies_){
        if(enemy.alive())
            return false;
    }
    return true;
}

void Level::handle_event(const sf::Event& event, sf::RenderWindow& window, Camera& camera) {
    slingshot_.handle_event(event, window);  
}


