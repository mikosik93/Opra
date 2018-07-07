#include <SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<iostream>
#include<vector>

#define TEX_FOLDER "C:\\Users\\User\\Desktop\\"

const int width = 800;
const int height = 800;

/*class Repository 
{
public:
	sf::Texture* getItem()
	{
		if (data == NULL)
		{
			// loadaj fajl
			//data = new sf::Texture();
			//data->loadFromFile(TEX_FOLDER"crvenajabuka.png");
			data = new sf::Texture();
			data->loadFromFile(TEX_FOLDER"crvenajabuka.png");
			
		}
		return data;
		
	}
	
private:
	sf::Texture* data;

};
*/
class Updatable
{
	public:
		virtual void Update(float deltaTime) {};
};

class ObjectOnScreen : public Updatable
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	float x = 0;
	float y = 0;

	void updatePosition()
	{
		this->sprite.setPosition(this->x, this->y);
	}
};
class Kosara :public ObjectOnScreen
{

	const unsigned int coorX = 767;
	const unsigned int coorY = 655;
	sf::IntRect coords = { 133,9,coorX,coorY };
	float scale = 0.15f;
	float step = 0.9f;
	float pocetak = 0;
	float kraj = 0;


public:
	float setStep(float noviStep)
	{
		return this->step = noviStep;
	}

	sf::Sprite& getSprite()
	{
		return this->sprite;
	}
	Kosara()
	{
		texture.loadFromFile(TEX_FOLDER"korpa.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(coords);
		sprite.scale(this->scale, this->scale);
		this->x = width / 2 - (this->coorX*this->scale) / 2;
		this->y = 701.75;
		this->pocetak = x + 10;
		this->kraj = x + 90;
		updatePosition();

	};
	
	float ipsilon()
	{
		return this->y;
	}
	float iks()
	{
		return this->x;
	}
	void Update(float deltaTime) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->x += this->step;
			this->pocetak = this->x + 10;
			this->kraj = this->x + 90;
			if (this->x > 674.95f)
				this->x = 674.95f;
			updatePosition();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->x -= this->step;
			this->pocetak = this->x + 10;
			this->kraj = this->x + 90;
			if (this->x <= 10)
				this->x = 10;
			updatePosition();
		}

	}
};

class Jabuka : public ObjectOnScreen
{
	const unsigned int coorX = 100;
	const unsigned int coorY = 1702;
	const float scale = 0.03f;
	const float step = 0.70f;
	const float beginX;
	const float beginY;

public:

	
	sf::Sprite& getSprite()
	{
		return this->sprite;
	};
	
	Jabuka (float initX, float initY): beginX(initX), beginY (initY)
	{
		//Repository r;
		//auto texture = r.getItem();
		texture.loadFromFile(TEX_FOLDER"crvenajabuka.png");
		sprite.setTexture(texture);
		sprite.scale(this->scale, this->scale);
		this->x = initX;
		this->y = initY;
		updatePosition();	
	}

	void Update(float deltaTime) override
	{
		this->y += this->step;
		updatePosition();;
	}
	float ipsilon()
	{
		return this->y;
	}
	float sredina()
	{
		float sredina = this->x - (this->coorX*this->scale) / 2;
		return sredina;	
	}

	bool TreveledToFar()
	{
		bool TreveledToFar = this->y > 790;
		return TreveledToFar;
	}
};

int main()
{
	srand(time(NULL));
	// create the window
	sf::RenderWindow prozor(sf::VideoMode(width,height), "OPRA");
	
														/* S E T U P */
	sf::Sprite timer;
	sf::Texture brojac;
	brojac.loadFromFile(TEX_FOLDER"brojevi.png");
	timer.setTexture(brojac);
	timer.setTextureRect({ 17,17,179,175 });
	timer.scale(0.20f, 0.20f);
	timer.setPosition(600, 10);
	sf::Sprite timer1;
	sf::Texture brojac1;
	brojac1.loadFromFile(TEX_FOLDER"brojevi.png");
	timer1.setTexture(brojac1);
	timer1.setTextureRect({ 204,22,179,165 });
	timer1.scale(0.20f, 0.20f);
	timer1.setPosition(640, 10);
	sf::Sprite timer2;
	sf::Texture brojac2;
	brojac2.loadFromFile(TEX_FOLDER"brojevi.png");
	timer2.setTexture(brojac2);
	timer2.setTextureRect({ 391,20,178,169 });
	timer2.scale(0.20f, 0.20f);
	timer2.setPosition(720,10);
	sf::Sprite timer3;
	sf::Texture brojac3;
	brojac3.loadFromFile(TEX_FOLDER"brojevi.png");
	timer3.setTexture(brojac3);
	timer3.setTextureRect({ 577,18,179,173 });
	timer3.scale(0.20f, 0.20f);
	timer3.setPosition(760, 10);
	

	std::vector<sf::Drawable*>drowables;
	std::vector<Jabuka*> jabuke;
	
	sf::Sprite pozadina;
	sf::Texture livada;
	livada.loadFromFile(TEX_FOLDER"pozadina.png");
	pozadina.scale(1.34f, 1.34f);
	pozadina.setTexture(livada);
	
	Kosara korpa;
	Jabuka crvenaJ((width / 2) - (1560*0.02) / 2,5);

	sf::Sprite* ptr = &crvenaJ.getSprite();

	drowables.push_back(&pozadina);
	drowables.push_back(&korpa.getSprite());
	//drowables.push_back(&crvenaJ.getSprite());

	int rezultat = 0;
	sf::Clock sat;
	sf::Clock animationTimer;
	sf::Clock okidac;

	sf::SoundBuffer soundbuffer;
	sf::Sound sound;

	//sf::Music music;

	soundbuffer.loadFromFile(TEX_FOLDER"pipe.wav");
	sound.setBuffer(soundbuffer);
	//music.openFromFile(TEX_FOLDER"tetris.ogg");
	
	int currentSecond = animationTimer.getElapsedTime().asSeconds();
	unsigned currentFrames = 0;
	float brzina = 1.20f;
	// run the program as long as the window is open
	while (prozor.isOpen())
	{
		
		float okidaC = okidac.getElapsedTime().asSeconds();
		auto lapsedTime=sat.restart();
		auto deltaTime = lapsedTime.asMilliseconds();

		if (currentSecond < (int)animationTimer.getElapsedTime().asSeconds())
		{
			currentSecond = animationTimer.getElapsedTime().asSeconds();
			//std::cout <<"Frames: "<< currentFrames << std::endl;
			currentFrames = 0;
		}
		//music.play();
														/* U P D A T E */
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		
		while (prozor.pollEvent(event))
		{
			
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				prozor.close();
			if (event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Escape)
				prozor.close();		
		}	
		switch (currentSecond)
		{
		case 0 : 
			brzina = 2.20f;
			break;
		case 10:
			brzina = 2.0f;
			break;
		case 20:
			brzina = 1.80f;
			break;
		case 30:
			brzina = 1.60f;
			break;
		case 40:
			brzina = 1.40f;
			break;
		case 50:
			korpa.setStep(1.5f);
			brzina = 0.80f;
			break;
		case 60:
			brzina = 0.70f;
			break;
		case 70:
			brzina = 0.50f;
			break;
		default:
			break;
		}
		
		if (okidaC>brzina) {
			auto ptr = new Jabuka((rand() % ((width - 60) - (width - 750))) + (width - 750), 5);
			jabuke.push_back(ptr);
			auto okidaC = okidac.restart();
		}
		korpa.Update(deltaTime);
	
		for (auto it =jabuke.begin(); it !=jabuke.end();++it)
		{
			auto crvenaJ = *it;
			crvenaJ->Update(deltaTime);
			

			if ((crvenaJ->ipsilon() >= korpa.ipsilon()-10 && crvenaJ->ipsilon()<=korpa.ipsilon()+10) &&
				(crvenaJ->sredina() >= (korpa.iks()-20) && crvenaJ->sredina() < korpa.iks()+80 ))
			{
				sound.play();
				rezultat += 10;
				std::cout << "Tvoj rezultat je: " << rezultat << std::endl;
				delete crvenaJ;
				*it = 0;
			}
			
			if (crvenaJ->TreveledToFar())
			{
				delete crvenaJ;
				*it = 0;
			}
		}
		for (auto it = jabuke.begin(); it != jabuke.end(); ++it)

		{
			if (*it == 0)
			{
				jabuke.erase(it);
				break;
			}
		}
		// clear the window with White color
		prozor.clear(sf::Color::White);
		
		//cJabuka.setPosition(crvenaJ.x, crvenaJ.y);
		//korpa.setPosition(korpa_x, korpa_y);
						
														/* D R A W */
						
		//prozor.draw(pozadina);
		//prozor.draw(korpa);
		//prozor.draw(cJabuka);	
		

		for (auto item : drowables)
		{
			prozor.draw(*item);
		}
		
		for (auto crvenaJ : jabuke)
		{
			prozor.draw(crvenaJ->getSprite());
		}
		prozor.draw(timer);
		prozor.draw(timer1);
		prozor.draw(timer2);
		prozor.draw(timer3);
		/* S H O W */
		// end the current frame
		prozor.display();
		currentFrames++;
		// limit number of fps
		auto frameDurationMs = sat.getElapsedTime().asMilliseconds();
		const auto minFrameDuration = 1000 / 30;
		if (frameDurationMs < minFrameDuration)
		{
			sf::sleep(sf::milliseconds(30) - sf::milliseconds(minFrameDuration));
		}
		
	}
	return 0;
}