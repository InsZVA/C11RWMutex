#include <mutex>
#include <condition_variable>

class RWMutex {
	private:
		
		std::mutex rm ,wm;
		std::unique_lock<std::mutex> rmtx, wmtx;
		std::condition_variable cond;
		int rd_cnt = 0;	//wait for read
		bool wr_cnt = false;	//wait for write
	public:
		RWMutex() : rmtx(rm, std::defer_lock), wmtx(wm, std::defer_lock) {}
		void rLock() {
			rmtx.lock();
			++rd_cnt;
			while (wr_cnt)
				cond.wait(rmtx);
			rmtx.unlock();
		}

		void rUnLock() {
			rmtx.lock();
			--rd_cnt;
			if (rd_cnt == 0)
				cond.notify_all();
			rmtx.unlock();
		}

		void wLock() {
 			wmtx.lock();
			while (wr_cnt || rd_cnt > 0)
				cond.wait(wmtx);
			wr_cnt = true;
			wmtx.unlock();
		}

		void wUnlock() {
			wmtx.lock();
			wr_cnt = false;
			cond.notify_all();
			wmtx.unlock();
		}
	};