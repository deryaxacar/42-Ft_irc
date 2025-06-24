NAME        = ircserv
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

SRC_DIR     = .
CMD_DIR     = Commands
MODES_DIR   = Modes

SRC_FILES   = main.cpp Server.cpp Commands.cpp

CMD_FILES   = \
	$(CMD_DIR)/Pass.cpp \
	$(CMD_DIR)/Nick.cpp \
	$(CMD_DIR)/User.cpp \
	$(CMD_DIR)/Join.cpp \
	$(CMD_DIR)/Quit.cpp \
	$(CMD_DIR)/Part.cpp \
	$(CMD_DIR)/Privmsg.cpp \
	$(CMD_DIR)/Kick.cpp \
	$(CMD_DIR)/Invite.cpp \
	$(CMD_DIR)/Topic.cpp \
	$(CMD_DIR)/Mode.cpp

MODES_FILES = \
	$(MODES_DIR)/Modes.cpp \
	$(MODES_DIR)/Invite.cpp \
	$(MODES_DIR)/Key.cpp \
	$(MODES_DIR)/Limit.cpp \
	$(MODES_DIR)/Op.cpp \
	$(MODES_DIR)/Topic.cpp

SRCS        = $(SRC_FILES) $(CMD_FILES) $(MODES_FILES)

OBJS        = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
