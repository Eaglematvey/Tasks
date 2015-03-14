#pragma once
#include<stack>
#include<assert.h>
	template <class T,class C = std::stack<T>>class Stack
	{
	public:
		typedef C container_type;
		typedef typename C::value_type value_type;
		typedef typename C::size_type size_type;
		typedef typename C::reference reference;
		typedef typename C::const_reference const_reference;
		Stack() {}
		virtual ~Stack() {}

		void push(const T& value);
		void pop();

		reference top()
		{
			return c.top();
		}
		const_reference top() const
		{
			return c.top();
		}
		bool empty() const
		{
			return c.empty();
		}
		size_type size() const
		{
			return c.size();
		}
		const value_type& min() const
		{
			assert(c.size() > 0 && m_min.size() > 0);

			return m_min.top();
		}
	private:
		container_type   c;     
		container_type  m_min;    
	};


	template <typename T,typename C>
	void Stack<T,C>::push(const T& value)
	{
		c.push(value);
		if (m_min.size() == 0 || value < m_min.top())
			m_min.push(value);
		else
			m_min.push(m_min.top());
	}

	template <typename T, typename C> 
	void Stack<T,C>::pop()
	{
		assert(c.size() > 0 && m_min.size() > 0);
		c.pop();
		m_min.pop();
	}
