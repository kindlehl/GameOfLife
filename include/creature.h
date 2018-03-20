#ifndef creature
#define creature

class Creature{
	friend class Grid;
	public:
		bool dead() const{ return m_dead; }
		bool alive() const{ return !m_dead; }
		Creature() :m_dead(true){}
		

	private:
		bool m_dead;

};


#endif
