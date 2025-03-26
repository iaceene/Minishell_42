#include "../../include/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

t_signal g_signal = {0};

static void handle_sigint(int sig)
{
    (void)sig;
    if (g_signal.interactive && !g_signal.in_execution)
    {
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void setup_interactive_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    g_signal.interactive = 1;
    g_signal.in_execution = 0;

    sa_int.sa_handler = &handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void setup_execution_signals(void)
{
    struct sigaction sa;

    g_signal.in_execution = 1;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

void setup_child_signals(void)
{
    struct sigaction sa;

    g_signal.interactive = 0;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

void restore_original_signals(void)
{
    setup_interactive_signals();
}