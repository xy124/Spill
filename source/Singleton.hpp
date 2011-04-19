#ifndef __SINGLETON
#define __SINGLETON

#include <cstring> // NULL

template <class T>
class TSingleton {
	protected://die erber dürfens nciht überschreiben
		static T* m_pSingleton;
	public:
		virtual ~TSingleton() {}; //erber überschreibens
	public:
		inline static T* get() {
			if (m_pSingleton == NULL)							
				m_pSingleton = new T();
			return m_pSingleton;
		}

		static void del() {
			if (m_pSingleton != NULL) {
				delete (m_pSingleton);
				m_pSingleton = NULL;
			}
		}
};


template <class T>
T* TSingleton<T>::m_pSingleton = NULL;
			
		


#endif
