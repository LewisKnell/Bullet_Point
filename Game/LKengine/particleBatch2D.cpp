#include "stdafx.h"
#include "particleBatch2D.h"

namespace LKengine {




	ParticleBatch2D::ParticleBatch2D()
	{
		// Empty
	}


	ParticleBatch2D::~ParticleBatch2D()
	{
		delete[] m_particles;
	}


	void ParticleBatch2D::init(int maxParticles, 
		float decayRate, 
		TileSheet texture,
		int tileID,
		std::function<void(Particle2D&, float)> updateFunc /* = defaultParticleUpdate */)
	{
		m_maxParticles = maxParticles;
		m_particles = new Particle2D[maxParticles];
		m_decayRate = decayRate;
		m_texture = texture;
		m_tileID = tileID;
		m_updateFunc = updateFunc;
	}


	void ParticleBatch2D::update(float deltaTime)
	{
		for (int i = 0; i < m_maxParticles; i++)
		{
			// Check if particle is active
			if (m_particles[i].life > 0.0f)
			{
				m_updateFunc(m_particles[i], deltaTime);
				m_particles[i].life -= m_decayRate * deltaTime;
			}
		}
	}


	void ParticleBatch2D::draw(SpriteBatch* spriteBatch)
	{
		//glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f); ///< Change this if using a sprite sheet to animate particles
		glm::vec4 uvRect;
		uvRect = m_texture.getUVsTopLeft(m_tileID);
		for (int i = 0; i < m_maxParticles; i++)
		{
			auto& p = m_particles[i]; ///< Make code cleaner
			// Check if particle is active
			if (p.life > 0.0f)
			{
				glm::vec4 destRect(p.position.x, p.position.y, p.width, p.width);
				spriteBatch->draw(destRect, uvRect, m_texture.texture.id, 0.0f, p.color, p.angle);
			}
		}
	}


	void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity,
		float angle,
		const ColorRGBA8& color,
		float width)
	{
		int particleIndex = findFreeParticle();

		auto& p = m_particles[particleIndex];

		p.life = 1.0f;
		p.position = position;
		p.velocity = velocity;
		p.angle = angle;
		p.color = color;
		p.width = width;

	}


	int ParticleBatch2D::findFreeParticle()
	{
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++)
		{
			if (m_particles[i].life <= 0.0f)
			{
				m_lastFreeParticle = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastFreeParticle; i++)
		{
			if (m_particles[i].life <= 0.0f)
			{
				m_lastFreeParticle = i;
				return i;
			}
		}
		// No particles are free, overwrite first particle
		return 0;
	}

}