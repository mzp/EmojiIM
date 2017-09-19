platform :osx, '10.11'

abstract_target 'App' do
  use_frameworks!
  pod 'ReactiveAutomaton', git: 'https://github.com/inamiy/ReactiveAutomaton'
  pod 'ReactiveCocoa'
  pod 'ReactiveSwift'
  pod '※ikemen'

  target 'EmojiIM'
  target 'UnitTest'
end

pod 'SwiftLint'

LegacySwiftPods = %w(ReactiveCocoa ReactiveSwift ReactiveAutomaton)

post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      if LegacySwiftPods.include? target.name
        config.build_settings['SWIFT_VERSION'] = '3.0'
      end
    end
  end
end
