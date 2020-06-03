/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_TEXTURE_MANAGER_DEF_H
#define TRAFFIC_SIM_MAIN_DRAWING_TEXTURE_MANAGER_DEF_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include <iostream>


namespace Drawing::Texture{

class Manager{
public:
    enum class TextureState{
        Removed,
        ExpectRemove,
        SetToRemove,
        Remain,
        Unknown
    };


    /**
     * @brief 
     * @details This class will be removed only when no one have it except for Texture::Manager.
     * 
     */
    class Texture{
        friend class Manager;

        sf::Texture texture_;
        sf::IntRect portion_;
        bool request_for_deleting;

        Texture(const std::string& path, const sf::IntRect& area = sf::IntRect());
        Texture(const sf::Texture& texture, const sf::IntRect& area = sf::IntRect());

    public:
        ~Texture();
        Texture(const Texture&) = delete;
        Texture(Texture&&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) = delete;

        void requestRemove();
        bool shouldBeRemoved();
        void resetRemoveRequest();
        TextureState getState();

        sf::Texture& getTexture();
        sf::IntRect& getRect();
    };

private:
    typedef std::map<std::string, std::shared_ptr<Texture>> MyMap; // used for storing textures

    MyMap textures_;

public:

    Manager();
    ~Manager();
    Manager(const Manager&) = delete;
    Manager(Manager&& other);
    Manager& operator=(Manager&& other);

    bool loadTexture(const std::string& path, const std::string& alias, const sf::IntRect& area = sf::IntRect());
    bool loadTexture(const std::string& path);

    TextureState freeTexture(const std::string& name);

    /**
     * @brief Save the texture that was created outside this object.
     * It copy the texture.
     * 
     * @param name - what name should be given to this texture
     * @param texture
     * @param rect
     * @return true - if saving did not succeeded
     * @return false - if saving did succeeded
     */
    bool saveTexture(const std::string& name, const sf::Texture& texture, const sf::IntRect& rect = sf::IntRect());

    /**
     * @brief Get the Texture object. 
     * @details If some object is connected with sf::Texture, then it should have an instance of shared_ptr.
     * Otherwise the Texture::Manager could delete texture without warning. 
     * 
     * @param name - name of the searched texture
     * @return std::shared_ptr<Texture>
     */
    std::shared_ptr<Texture> getTexture(const std::string& name) const;
};
}

#endif
