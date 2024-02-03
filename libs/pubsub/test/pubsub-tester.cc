
#include <gtest/gtest.h>

#include "pubsub-publisher.h"
#include "pubsub-subscriber.h"

TEST( PubsubTest, Basics ) {

  int value = 0;
  
  pubsub::Publisher<int> publisher;
  pubsub::Subscriber subscriber;
  
  publisher.subscribe( &subscriber, [&value]( int t_value ){ value = t_value; } );
  
  ASSERT_EQ( value, 0 );
  
  publisher.publish( 1 );
  ASSERT_EQ( value, 1 );
  
  ASSERT_EQ( publisher.getSubscriptionCount(), 1u );
  ASSERT_EQ( subscriber.getPublisherCount(), 1u );
  
  publisher.unsubscribe( &subscriber );
  ASSERT_EQ( publisher.getSubscriptionCount(), 0u );
  
  // Note: Publisher will remain listed here, cleared in destructor
  ASSERT_EQ( subscriber.getPublisherCount(), 1u );
  
  publisher.publish( 2 );
  ASSERT_EQ( value, 1 );
}

TEST( PubsubTest, SubscriberDestroyed ) {

  pubsub::Publisher<int> publisher;
  ASSERT_EQ( publisher.getSubscriptionCount(), 0u );
  
  {
    pubsub::Subscriber subscriber;
    publisher.subscribe( &subscriber, [](int){} );
    ASSERT_EQ( publisher.getSubscriptionCount(), 1u );
    ASSERT_EQ( subscriber.getPublisherCount(), 1u );
    ASSERT_NO_THROW( publisher.publish( 1 ) );
  }
  
  ASSERT_EQ( publisher.getSubscriptionCount(), 0u );
  ASSERT_NO_THROW( publisher.publish( 1 ) );
}

TEST( PubsubTest, PublisherDestroyed ) {

  pubsub::Subscriber subscriber;
  {
    pubsub::Publisher<int> publisher;
    publisher.subscribe( &subscriber, [](int){} );
    ASSERT_EQ( publisher.getSubscriptionCount(), 1u );
    ASSERT_EQ( subscriber.getPublisherCount(), 1u );
    ASSERT_NO_THROW( publisher.publish( 1 ) );
  }
  
  ASSERT_EQ( subscriber.getPublisherCount(), 0u );
}

TEST( PubsubTest, MemberFunctions ) {

  class MyClass {
  public:
    void func(int t_val) {
      m_val = t_val;
    }
    int m_val = 0;
  };
  
  MyClass obj;
  
  pubsub::Subscriber subscriber;
  pubsub::Publisher<int> publisher;
  publisher.subscribe( &subscriber, &obj, &MyClass::func );
  
  publisher.publish( 1 );
  ASSERT_EQ( obj.m_val, 1 );
}

TEST( PubsubTest, Fowarding ) {

  int val = 0;
  
  pubsub::Subscriber subscriber1;
  pubsub::Subscriber subscriber2;
  pubsub::Publisher<int> publisher1;
  pubsub::Publisher<int> publisher2;
  
  publisher1.forward( &subscriber1, publisher2 );
  publisher2.subscribe( &subscriber2, [&val]( int t_val ){ val = t_val; } );
  
  publisher1.publish( 1 );
  ASSERT_EQ( val, 1 );
}

TEST( PubsubTest, MultipleArgs ) {

  bool boolVal = false;
  int intVal = 0;
  std::string strVal = "";
  
  pubsub::Subscriber subscriber;
  pubsub::Publisher<bool,int,std::string> publisher;
  publisher.subscribe( &subscriber, [&boolVal,&intVal,&strVal]( bool b, int i, std::string s ){ 
    boolVal = b;
    intVal = i;
    strVal = s;
  });
  
  publisher.publish( true, 1, "Hello" );
  ASSERT_EQ( boolVal, true );
  ASSERT_EQ( intVal, 1 );
  ASSERT_EQ( strVal, "Hello" );
}

template<typename T>
struct PubsubTypeTest : public ::testing::Test {};
TYPED_TEST_SUITE_P(PubsubTypeTest);

TYPED_TEST_P(PubsubTypeTest, Basics) {
  
  TypeParam value = 0;
  
  pubsub::Publisher<TypeParam> publisher;
  pubsub::Subscriber subscriber;
  publisher.subscribe( &subscriber, [&value]( int t_value ){ value = t_value; } );
  publisher.publish( 1 );
  ASSERT_EQ( value, 1 );
}

REGISTER_TYPED_TEST_SUITE_P(PubsubTypeTest, Basics);
using Types = testing::Types<bool, int, long long, std::size_t>;
INSTANTIATE_TYPED_TEST_SUITE_P(PubsubTest, PubsubTypeTest, Types);