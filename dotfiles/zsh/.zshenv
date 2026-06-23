# XDG Base Directory Specification
export XDG_CONFIG_HOME=~/.config
export XDG_DATA_HOME=~/.local/share
export XDG_CACHE_HOME=~/.cache
export XDG_STATE_HOME=~/.local/state

# Runtime relocations (depends on XDG_* above)
[[ -r "$ZDOTDIR/.zenv-runtime" ]] && source "$ZDOTDIR/.zenv-runtime"
