export CMAKE_PREFIX_PATH="~/.brew/Cellar/qt/5.15.1/"

cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build


