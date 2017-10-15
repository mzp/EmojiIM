require 'gemoji'
require 'json'

entries = Emoji.all.flat_map do |emoji|
  next [] unless emoji.raw
  emoji.aliases.map do |name|
    { name: ":#{name}:", emoji: emoji.raw }
  end
end
puts JSON.pretty_generate(entries)
